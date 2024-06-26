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

using namespace BnD;

D1Alarm::D1Alarm()
    : _serialNumber(-1)
    , _code(0)
    , _taskID(-1)
    , _zoneID(0)
    , _reason(0)
    , _commandID()
    , _carrierID()
    , _activateTime()
    , _clearTime()
    , _resolvedBy()
    , _data()
{
}

D1Alarm::D1Alarm(int64 serialNumber, int32 code, int32 taskID, int32 zoneID, int32 reason,
                 B1String&& commandID, B1String&& carrierID, B1String&& activateTime, B1String&& data)
    : _serialNumber(serialNumber)
    , _code(code)
    , _taskID(taskID)
    , _zoneID(zoneID)
    , _reason(reason)
    , _commandID(commandID)
    , _carrierID(carrierID)
    , _activateTime(activateTime)
    , _clearTime()
    , _resolvedBy()
    , _data(data)
{
}

D1Alarm::~D1Alarm()
{
}

void D1Alarm::appendRedisStringArgs(std::vector<B1String>* args, B1String&& key, int32 value) const
{
    if (value > 0) {
        args->push_back(std::move(key));
        args->push_back(B1String::formatAs("%d", value));
    }
}

void D1Alarm::appendRedisStringArgs(std::vector<B1String>* args, B1String&& key, const B1String& value) const
{
    if (value.isEmpty() != true) {
        args->push_back(std::move(key));
        args->push_back(value.copy());
    }
}

void D1Alarm::toRedisStringArgs(std::vector<B1String>* args) const
{
    args->reserve(20);
    args->push_back("HMSET");
    args->push_back(B1String::formatAs("System:Alarm:Record:%lld", _serialNumber));
    args->push_back("SerialNo");
    args->push_back(B1String::formatAs("%lld", _serialNumber));
    appendRedisStringArgs(args, "Code", _code);
    appendRedisStringArgs(args, "Location", _zoneID);
    appendRedisStringArgs(args, "ReasonCode", _reason);
    appendRedisStringArgs(args, "TaskID", _taskID);
    appendRedisStringArgs(args, "CommandID", _commandID);
    appendRedisStringArgs(args, "CarrierID", _carrierID);
    appendRedisStringArgs(args, "SetTime", _activateTime);
    appendRedisStringArgs(args, "ClearTime", _clearTime);
    appendRedisStringArgs(args, "ResolvedBy", _resolvedBy);
    appendRedisStringArgs(args, "Data", _data);
}

void D1Alarm::fromRedisMap(const std::map<B1String, B1String>& map)
{
#ifndef SET_FROM_REDIS_MAP
#define SET_FROM_REDIS_MAP_INT64(k, v) itr = map.find(k); if (itr != map.end() && itr->second.isEmpty() != true) v = itr->second.toInt64(); else v = -1;
#define SET_FROM_REDIS_MAP_INT32(k, v) itr = map.find(k); if (itr != map.end() && itr->second.isEmpty() != true) v = itr->second.toInt32(); else v = -1;
#define SET_FROM_REDIS_MAP_STRING(k, v) itr = map.find(k); if (itr != map.end() && itr->second.isEmpty() != true) v = itr->second.copy(); else v.clear();
#endif
    std::map<B1String, B1String>::const_iterator itr;
    try {
        SET_FROM_REDIS_MAP_INT64("SerialNo", _serialNumber);
        SET_FROM_REDIS_MAP_INT32("Code", _code);
        SET_FROM_REDIS_MAP_INT32("Location", _zoneID);
        SET_FROM_REDIS_MAP_INT32("ReasonCode", _reason);
        SET_FROM_REDIS_MAP_INT32("TaskID", _taskID);
        SET_FROM_REDIS_MAP_STRING("CommandID", _commandID);
        SET_FROM_REDIS_MAP_STRING("CarrierID", _carrierID);
        SET_FROM_REDIS_MAP_STRING("SetTime", _activateTime);
        SET_FROM_REDIS_MAP_STRING("ClearTime", _clearTime);
        SET_FROM_REDIS_MAP_STRING("ResolvedBy", _resolvedBy);
        SET_FROM_REDIS_MAP_STRING("Data", _data);
    }
    catch (...) { assert(false); }
}
