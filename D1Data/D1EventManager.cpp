//
// D1EventManager.cpp
//
// Library: D1Data
// Package: D1Data
// Module:  D1Data
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Data.h"
#include "D1EventManager.h"

#include <B1Base/B1Time.h>

#include <D1Base/D1Consts.h>
#include <D1Base/D1RedisClientInterface.h>
#include <D1Message/D1MsgEventNtf.h>

using namespace BnD;

D1EventManager::D1EventManager(B1String&& channel)
    : _channel(channel)
    , _redisClientInterface(NULL)
{
}

D1EventManager::~D1EventManager()
{
}

bool D1EventManager::getTaskTransferInfo(int64 taskID, B1String* commandID, B1String* carrierID)
{
    B1String key;
    key.format("TransferInfo:%d", taskID);
    std::vector<B1String> fields(2), out;
    fields[0] = "CommandID";
    fields[1] = "CarrierID";
    _redisClientInterface->hmget(key, fields, &out);
    *commandID = std::move(out[0]);
    *carrierID = std::move(out[1]);
    return carrierID->isEmpty() != true;
}

void D1EventManager::initialize(D1RedisClientInterface* redisClientInterface)
{
    _redisClientInterface = redisClientInterface;
}

void D1EventManager::finalize()
{
    _redisClientInterface = NULL;
}

bool D1EventManager::addEvent(int32 code, const B1String& commandID, const B1String& carrierID, int64 taskID, int32 zoneID, int32 reason, bool isEssential)
{
    uint64 seconds = 0;
    uint32 microseconds = 0;
    if (_redisClientInterface->time(&seconds, &microseconds) != true) {
        return false;
    }
    D1MsgEventNtf info(code);
    info.setCarrierID(carrierID.copy());
    info.setTaskID(taskID);
    info.setZoneID(zoneID);
    info.setReason(reason);
    B1String json;
    info.composeToJson(&json);
    _redisClientInterface->publish(_channel, json, isEssential);
    return true;
}

bool D1EventManager::addEvent(int32 code)
{
    return addEvent(code, D1Consts::ID_INVALID, D1Consts::ID_INVALID, 0);
}

bool D1EventManager::addEvent(int32 code, int32 zoneID)
{
    return addEvent(code, D1Consts::ID_INVALID, zoneID, 0);
}

bool D1EventManager::addEvent(int32 code, int64 taskID, int32 zoneID, int32 reason, bool isEssential)
{
    B1String commandID, carrierID;
    if (getTaskTransferInfo(taskID, &commandID, &carrierID) != true) {
        return addEvent(code, "N/A", "N/A", taskID, zoneID, reason, isEssential);
    }
    else {
        return addEvent(code, commandID, carrierID, taskID, zoneID, reason, isEssential);
    }
}
