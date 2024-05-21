//
// D1WarningManager.cpp
//
// Library: D1Data
// Package: D1Data
// Module:  D1Data
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Data.h"
#include "D1WarningManager.h"

#include <B1Base/B1Time.h>

#include <D1Base/D1RedisClientInterface.h>

using namespace BnD;

D1WarningManager::D1WarningManager(B1String&& channel)
    : D1EventManager(std::move(channel))
{
}

bool D1WarningManager::addWarning(int32 code, const B1String &commandID, const B1String &carrierID, int32 taskID, int32 zoneID, int32 reason)
{
    int64 serialNumber = makeNewSerialNumber();
    if (serialNumber < 0)
        return false;
    B1String setTime;
    _redisClientInterface->time(&setTime);
    B1Archive archive, messageData;
    archive.writeData("MessageID", B1String("tcsWarningSet"));    

    messageData.writeData("CommandID", commandID);
    messageData.writeData("CarrierID", carrierID);
    messageData.writeData("Time", setTime);
    messageData.writeData("TaskID", taskID);
    messageData.writeData("SerialNo", serialNumber);
    messageData.writeData("EventCode", code);
    messageData.writeData("Location", zoneID);
    messageData.writeData("Reason", reason);
    messageData.writeData("BaseTime", B1Time::currentTimeInMilliseconds());

    archive.addSubArchive("MessageData", messageData);

    B1String message;
    archive.toString(&message);
    
    _redisClientInterface->publish(_channel, message, false);
    return true;
}

bool D1WarningManager::addWarning(int32 code)
{
    return addWarning(code, -1, -1, 0);
}

bool D1WarningManager::addWarning(int32 code, int32 zoneID)
{
    return addWarning(code, -1, zoneID, 0);
}

bool D1WarningManager::addWarning(int32 code, int32 taskID, int32 zoneID, int32 reason)
{
    B1String commandID, carrierID;
    if (getTaskTransferInfo(taskID, &commandID, &carrierID) != true)
        return addWarning(code, "N/A", "N/A", taskID, zoneID, reason);
    else
        return addWarning(code, commandID, carrierID, taskID, zoneID, reason);
}
