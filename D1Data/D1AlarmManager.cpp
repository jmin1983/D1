//
// D1AlarmManager.cpp
//
// Library: D1Data
// Package: D1Data
// Module:  D1Data
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Data.h"
#include "D1AlarmManager.h"
#include "D1Alarm.h"

#include <B1Base/B1Lock.h>

#include <D1Base/D1Consts.h>
#include <D1Base/D1RedisClientInterface.h>
#include <D1Message/D1MsgAlarmClearRsp.h>
#include <D1Message/D1MsgAlarmNtf.h>
#include <D1Message/D1MessageSender.h>
#include <D1EQData/D1Zone.h>
#include <D1EQData/D1ZoneRepository.h>
#include <D1EQData/D1ZoneStateAttributes.h>

using namespace BnD;

D1AlarmReader::D1AlarmReader()
    : _redisClientInterface(NULL)
{
}

D1AlarmReader::~D1AlarmReader()
{
}

void D1AlarmReader::implInitialize(D1RedisClientInterface* redisClientInterface)
{
    _redisClientInterface = redisClientInterface;
}

void D1AlarmReader::implFinalize()
{
    _redisClientInterface = NULL;
}

void D1AlarmReader::initialize(D1RedisClientInterface* redisClientInterface)
{
    implInitialize(redisClientInterface);
}

void D1AlarmReader::finalize()
{
    implFinalize();
}

auto D1AlarmReader::getAlarmInfo(int64 serialNumber) const -> std::shared_ptr<D1Alarm>
{
    auto alarm = std::make_shared<D1Alarm>(serialNumber);
    alarm->readFromRedis(_redisClientInterface);
    return alarm;
}

auto D1AlarmReader::getAllAlarmInfos() const -> std::list<std::shared_ptr<D1Alarm> >
{
    std::list<std::shared_ptr<D1Alarm> > result;
    std::set<B1String> keys;
    _redisClientInterface->scan(D1Alarm::alarmKey() + ":*[0-9]", &keys);
    for (const auto& key : keys) {
        std::map<B1String, B1String> out;
        if (_redisClientInterface->hgetall(key, &out) != true) {
            continue;
        }
        int64 serialNumber = D1Consts::ID_INVALID;
        try {
            serialNumber = key.substring(D1Alarm::alarmKey().length() + 1).toInt64();
        }
        catch (...) {
            continue;
        }
        if (auto alarm = getAlarmInfo(serialNumber)) {
            result.push_back(alarm);
        }
    }
    return result;
}

D1AlarmWriter::D1AlarmWriter()
    : D1AlarmReader()
    , _alarmLock(new B1Lock())
{
}

void D1AlarmWriter::onAlarmAdded(int64 serialNumber, int32 code, int32 serviceID, int64 taskID, int32 reason, const D1Zone* zone, const B1String& carrierID, const B1String& data)
{
    B1LOG("alarm added: serialNumber[%lld], code[%d], serviceID[%d], taskID[%lld], reason[%d], zoneID[%d], carrierID[%s], data[%s]",
        serialNumber, code, serviceID, taskID, reason, zone ? zone->zoneID() : D1Consts::ID_INVALID, carrierID.cString(), data.cString());
}

void D1AlarmWriter::onAlarmCleared(int64 serialNumber, int32 serviceID, int32 zoneID)
{
    B1LOG("alarm cleared: serialNumber[%lld], serviceID[%d], zoneID[%d]", serialNumber, serviceID, zoneID);
}

int64 D1AlarmWriter::makeNewSerialNumber()
{
    return implMakeNewSerialNumber();
}

bool D1AlarmWriter::addAlarm(int32 code, int32 serviceID, int64 taskID, int32 reason)
{
    return addAlarm(code, serviceID, taskID, reason, NULL);
}

bool D1AlarmWriter::addAlarm(int32 code, int32 serviceID, int64 taskID, int32 reason, const D1Zone* zone)
{
    return addAlarm(code, serviceID, taskID, reason, zone, "", "");
}

bool D1AlarmWriter::addAlarm(int32 code, int32 serviceID, int64 taskID, int32 reason, const D1Zone* zone, const B1String& carrierID, B1String&& data)
{
    if (zone && zone->zoneID() != D1Consts::ID_INVALID) {
        if (D1ZoneRepository::isOwnerZone(zone->zoneID(), serviceID) != true) {
            assert(false);  //  only owner can generate the alarm.
            return false;
        }
    }
    int64 serialNumber = makeNewSerialNumber();
    if (D1Consts::ID_INVALID == serialNumber) {
        return false;
    }
    if (zone) {
        {
            B1AutoLock al(*_alarmLock);
            if (zone->stateAttributes()->isAlarmed()) {
                return false;
            }
            zone->stateAttributes()->setAlarmed(serialNumber, NULL);
        }
        zone->stateAttributes()->notifyAttributesChanged(_redisClientInterface, true);
    }
    onAlarmAdded(serialNumber, code, serviceID, taskID, reason, zone, carrierID, data);

    D1MsgAlarmNtf info(serialNumber, code);
    info.setReason(reason);
    info.setServiceID(serviceID);
    info.setTaskID(taskID);
    info.setCarrierID(carrierID.copy());
    if (zone) {
        info.setZoneID(zone->zoneID());
    }
    B1String json;
    info.composeToJsonWithBaseTime(&json);
    return _redisClientInterface->publish(D1MessageSender::alarmEventChannel(), json, true);
}

bool D1AlarmWriter::clearAlarm(int64 serialNumber, int32 serviceID)
{
    return clearAlarm(serialNumber, serviceID, NULL);
}

bool D1AlarmWriter::clearAlarm(int64 serialNumber, int32 serviceID, const D1Zone* zone)
{
    if (zone && zone->zoneID() != D1Consts::ID_INVALID) {
        if (D1ZoneRepository::isOwnerZone(zone->zoneID(), serviceID) != true) {
            assert(false);  //  only owner can clear the alarm.
            B1LOG("unable to clear alarm if not a zone owner: zoneID[%d], serviceID[%d]", zone->zoneID(), serviceID);
            D1MsgAlarmClearRsp rsp(serialNumber, serviceID, zone ? zone->zoneID() : D1Consts::ID_INVALID, false);
            B1String json;
            rsp.composeToJsonWithBaseTime(&json);
            _redisClientInterface->publish(D1MessageSender::alarmEventChannel(), json, false);
            return false;
        }
    }
    if (auto alarm = getAlarmInfo(serialNumber)) {
        if (alarm->zoneID() != D1Consts::ID_INVALID) {
            if (D1ZoneRepository::isOwnerZone(alarm->zoneID(), serviceID) != true) {
                B1LOG("unable to clear zone_alarm if not a zone owner: zoneID[%d], serviceID[d]", alarm->zoneID(), serviceID);
                D1MsgAlarmClearRsp rsp(serialNumber, serviceID, zone ? zone->zoneID() : D1Consts::ID_INVALID, false);
                B1String json;
                rsp.composeToJsonWithBaseTime(&json);
                _redisClientInterface->publish(D1MessageSender::alarmEventChannel(), json, false);
                return false;
            }
        }
    }

    _redisClientInterface->del(D1Alarm::redisKey(serialNumber));
    if (zone) {
        {
            B1AutoLock al(*_alarmLock);
            zone->stateAttributes()->clearAlarmed(NULL);
        }
        zone->stateAttributes()->notifyAttributesChanged(_redisClientInterface, true);
    }
    onAlarmCleared(serialNumber, serviceID, zone ? zone->zoneID() : D1Consts::ID_INVALID);

    D1MsgAlarmClearRsp rsp(serialNumber, serviceID, zone ? zone->zoneID() : D1Consts::ID_INVALID, true);
    B1String json;
    rsp.composeToJsonWithBaseTime(&json);
    return _redisClientInterface->publish(D1MessageSender::alarmEventChannel(), json, true);
}
