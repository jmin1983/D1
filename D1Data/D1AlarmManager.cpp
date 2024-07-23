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

using namespace BnD;

D1AlarmReader::D1AlarmReader()
    : _prefixRecord("System:Alarm:Record:")
    , _keyActive("System:Alarm:ActiveAlarms")
    , _redisClientInterface(NULL)
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

bool D1AlarmReader::getTaskTransferInfo(int32 taskID, B1String* commandID, B1String* carrierID)
{
    B1String key;
    key.format("TransferInfo:%d", taskID);
    std::vector<B1String> fields(2), out;
    fields[0] = "CommandID";
    fields[1] = "CarrierID";
    _redisClientInterface->hmget(key, fields, &out);
    *commandID = std::move(out[0]);
    *carrierID = std::move(out[1]);
    return commandID->isEmpty() != true;
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
    B1String key;
    key.format("%s%lld", _prefixRecord.cString(), serialNumber);
    std::map<B1String, B1String> out;
    if (_redisClientInterface->hgetall(key, &out) != true) {
        return std::shared_ptr<D1Alarm>();
    }
    auto alarm(std::make_shared<D1Alarm>());
    alarm->fromRedisMap(std::move(out));
    return alarm;
}

bool D1AlarmReader::getActiveAlarmSerialNumbers(std::set<int64>* serialNumbers) const
{
    std::list<B1String> out;
    if (_redisClientInterface->smembers(_keyActive, &out) != true) {
        return false;
    }
    for (const auto& o : out) {
        try {
            int32 alarm = o.toInt32();
            if (alarm != D1Consts::ID_INVALID) {
                serialNumbers->insert(alarm);
            }
        }
        catch (...) {}
    }
    return true;
}

bool D1AlarmReader::getActiveAlarmCodes(std::set<int32>* codes) const
{
    std::set<int64> serialNumbers;
    if (getActiveAlarmSerialNumbers(&serialNumbers) != true)
        return false;
    for (auto serialNumber : serialNumbers) {
        if (auto alarm = getAlarmInfo(serialNumber)) {
            codes->insert(alarm->code());
        }
    }
    return true;
}

bool D1AlarmReader::isAlarmActivated() const
{
    std::set<int64> serialNumbers;
    getActiveAlarmSerialNumbers(&serialNumbers);
    return serialNumbers.empty() != true;
}

bool D1AlarmReader::isAlarmActivated(int32 zoneID) const
{
    std::set<int64> serialNumbers;
    if (getActiveAlarmSerialNumbers(&serialNumbers) != true)
        return false;
    for (auto serialNumber : serialNumbers) {
        if (auto alarm = getAlarmInfo(serialNumber)) {
            if (alarm->zoneID() == zoneID) {
                return true;
            }
        }
    }
    return false;
}

int64 AlarmWriter::makeNewSerialNumber()
{
    return implMakeNewSerialNumber();
}
