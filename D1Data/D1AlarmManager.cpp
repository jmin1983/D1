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

#include <D1Base/D1Consts.h>
#include <D1Base/D1RedisClientInterface.h>
#include <D1Message/D1MessageSender.h>
#include <D1Message/D1MsgEventNtf.h>
#include <D1EQData/D1ZoneRepository.h>

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
{
}

int64 D1AlarmWriter::makeNewSerialNumber()
{
    return implMakeNewSerialNumber();
}

bool D1AlarmWriter::clearAlarm(int64 serialNumber, int32 serviceID, const B1String& resolvedBy)
{
    auto alarm = getAlarmInfo(serialNumber);
    if (alarm == NULL) {
        return false;
    }
    if (alarm->zoneID() != D1Consts::ID_INVALID) {
        if (D1ZoneRepository::isOwnerZone(alarm->zoneID(), serviceID) != true) {
            assert(false);  //  only owner can clear the alarm.
            return false;
        }
    }
    assert(false);  //  todo: implement.
    return false;
}

bool D1AlarmWriter::addAlarm(int32 code, int32 serviceID, int32 zoneID, int64 taskID, int32 reason)
{
    assert(false);  //  todo: implement.
    return false;
}

bool D1AlarmWriter::addAlarm(int32 code, int32 serviceID, int32 zoneID, int64 taskID, int32 reason, B1String&& carrierID, B1String&& data)
{
    assert(false);  //  todo: implement.
    return false;
}
