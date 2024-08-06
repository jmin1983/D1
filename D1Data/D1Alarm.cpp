//
// D1Alarm.cpp
//
// Library: D1Data
// Package: D1Data
// Module:  D1Data
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Data.h"
#include "D1Alarm.h"

#include <D1Base/D1Consts.h>

using namespace BnD;

const B1String D1Alarm::_alarmKey("Alarm");

D1Alarm::D1Alarm(int64 serialNumber)
    : _serialNumber("SerialNumber", serialNumber)
    , _code("Code", 0)
    , _taskID("TaskID", D1Consts::ID_INVALID)
    , _zoneID("ZoneID", D1Consts::ID_INVALID)
    , _serviceID("ServiceID", D1Consts::SERVICE_ID_INVALID)
    , _reason("Reason", 0)
    , _carrierID("CarrierID", "")
    , _data("Data", "")
{
}

D1Alarm::D1Alarm(int64 serialNumber, int32 code, int64 taskID, int32 zoneID, int32 serviceID, int32 reason, B1String&& carrierID, B1String&& data)
    : _serialNumber("SerialNumber", serialNumber)
    , _code("Code", code)
    , _taskID("TaskID", taskID)
    , _zoneID("ZoneID", zoneID)
    , _serviceID("ServiceID", serviceID)
    , _reason("Reason", reason)
    , _carrierID("CarrierID", std::move(carrierID))
    , _data("Data", std::move(data))
{
}

D1Alarm::~D1Alarm()
{
}

B1String D1Alarm::redisKey() const
{
    return redisKey(serialNumber());
}

bool D1Alarm::isValidToMakeRedisString() const
{
    return serialNumber() != D1Consts::ID_INVALID;
}

void D1Alarm::makeRedisStringArgs(std::vector<B1String>* args) const
{
    setRedisString(args, _code);
    setRedisString(args, _taskID);
    setRedisString(args, _zoneID);
    setRedisString(args, _serviceID);
    setRedisString(args, _reason);
    setRedisString(args, _carrierID);
    setRedisString(args, _data);
}

bool D1Alarm::readRedisMap(const std::map<B1String, B1String>& map)
{
    readFromRedisMap(map, &_code);
    readFromRedisMap(map, &_taskID);
    readFromRedisMap(map, &_zoneID);
    readFromRedisMap(map, &_serviceID);
    readFromRedisMap(map, &_reason);
    readFromRedisMap(map, &_carrierID);
    readFromRedisMap(map, &_data);
    return true;
}

B1String D1Alarm::redisKey(int64 serialNumber)
{
    assert(serialNumber != D1Consts::ID_INVALID);
    return serialNumber != D1Consts::ID_INVALID ? B1String::formatAs("%s:%lld", _alarmKey.cString(), serialNumber) : "";
}

