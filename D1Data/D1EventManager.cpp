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

#include <D1Base/D1RedisClientInterface.h>

using namespace BnD;

D1EventManager::D1EventManager(B1String&& channel)
    : _channel(channel)
    , _redisClientInterface(NULL)
{
}

D1EventManager::~D1EventManager()
{
}

int64 D1EventManager::implMakeNewSerialNumber()
{
    const static B1String key = "System:Event:EventSerialNo";
    int64 result = -1;
    if (_redisClientInterface->incr(key, &result) != true) {
        return -1;
    }
    return result;
}

int64 D1EventManager::makeNewSerialNumber()
{
    return implMakeNewSerialNumber();
}

bool D1EventManager::getTaskTransferInfo(int32 taskID, B1String* commandID, B1String* carrierID)
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

bool D1EventManager::addEvent(int32 code, const B1String& commandID, const B1String& carrierID, int32 taskID, int32 zoneID, int32 reason, bool isEssential)
{
    int64 serialNumber = makeNewSerialNumber();
    if (serialNumber < 0) {
        return false;
    }
    uint64 seconds = 0;
    uint32 microseconds = 0;
    if (_redisClientInterface->time(&seconds, &microseconds)) {
        return false;
    }
    B1Archive archive, messageData;
    archive.writeData("MessageID", B1String("tcsEventSet"));

    messageData.writeData("CommandID", commandID);
    messageData.writeData("CarrierID", carrierID);
    messageData.writeData("Time", seconds);
    messageData.writeData("SerialNo", serialNumber);
    messageData.writeData("TaskID", taskID);
    messageData.writeData("EventCode", code);
    messageData.writeData("Location", zoneID);
    messageData.writeData("Reason", reason);
    messageData.writeData("BaseTime", B1Time::currentTimeInMilliseconds());

    archive.addSubArchive("MessageData", messageData);

    B1String message;
    archive.toString(&message);
    _redisClientInterface->publish(_channel, message, isEssential);

    return true;
}

bool D1EventManager::addEvent(int32 code)
{
    return addEvent(code, -1, -1, 0);
}

bool D1EventManager::addEvent(int32 code, int32 zoneID)
{
    return addEvent(code, -1, zoneID, 0);
}

bool D1EventManager::addEvent(int32 code, int32 taskID, int32 zoneID, int32 reason, bool isEssential)
{
    B1String commandID, carrierID;
    if (getTaskTransferInfo(taskID, &commandID, &carrierID) != true) {
        return addEvent(code, "N/A", "N/A", taskID, zoneID, reason, isEssential);
    }
    else {
        return addEvent(code, commandID, carrierID, taskID, zoneID, reason, isEssential);
    }
}
