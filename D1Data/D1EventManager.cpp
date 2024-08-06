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

#include <D1Base/D1Consts.h>
#include <D1Base/D1RedisClientInterface.h>
#include <D1Message/D1MessageSender.h>
#include <D1Message/D1MsgEventNtf.h>

using namespace BnD;

D1EventManager::D1EventManager()
    : _redisClientInterface(NULL)
{
}

D1EventManager::~D1EventManager()
{
}

void D1EventManager::initialize(D1RedisClientInterface* redisClientInterface)
{
    _redisClientInterface = redisClientInterface;
}

void D1EventManager::finalize()
{
    _redisClientInterface = NULL;
}

bool D1EventManager::addEvent(int32 code, int32 serviceID, bool isEssential)
{
    return addEvent(code, serviceID, D1Consts::ID_INVALID, D1Consts::ID_INVALID, 0, "", isEssential);
}

bool D1EventManager::addEvent(int32 code, int32 serviceID, int32 zoneID, bool isEssential)
{
    return addEvent(code, serviceID, zoneID, D1Consts::ID_INVALID, 0, "", isEssential);
}

bool D1EventManager::addEvent(int32 code, int32 serviceID, int32 zoneID, int64 taskID, int32 reason, bool isEssential)
{
    return addEvent(code, serviceID, zoneID, taskID, reason, "", isEssential);
}

bool D1EventManager::addEvent(int32 code, int32 serviceID, int32 zoneID, int64 taskID, int32 reason, B1String&& carrierID, bool isEssential)
{
    D1MsgEventNtf info(code);
    info.setCarrierID(std::move(carrierID));
    info.setTaskID(taskID);
    info.setZoneID(zoneID);
    info.setReason(reason);
    info.setServiceID(serviceID);
    B1String json;
    info.composeToJson(&json, false);
    return _redisClientInterface->publish(D1MessageSender::alarmEventChannel(), json, isEssential);
}
