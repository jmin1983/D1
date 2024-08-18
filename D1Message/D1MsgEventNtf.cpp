//
// D1MsgEventNtf.cpp
//
// Library: D1Message
// Package: AlarmEvent
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Message.h"
#include "D1MsgEventNtf.h"

#include <D1Base/D1Consts.h>

using namespace BnD;

D1MsgEventNtf::D1MsgEventNtf(int32 code)
    : D1BaseMessage()
    , _serialNumber("SerialNumber", D1Consts::ID_INVALID)
    , _taskID("TaskID", D1Consts::ID_INVALID)
    , _time("Time", 0)
    , _zoneID("ZoneID", D1Consts::ID_INVALID)
    , _serviceID("ServiceID", D1Consts::SERVICE_ID_INVALID)
    , _code("Code", code)
    , _reason("Reason", D1Consts::ID_INVALID)
    , _carrierID("CarrierID", "")
{
    _messageID.second = messageString().copy();
}

D1MsgEventNtf::D1MsgEventNtf(D1BaseMessage&& baseMessage)
    : D1BaseMessage(std::move(baseMessage))
    , _serialNumber("SerialNumber", D1Consts::ID_INVALID)
    , _taskID("TaskID", D1Consts::ID_INVALID)
    , _time("Time", 0)
    , _zoneID("ZoneID", D1Consts::ID_INVALID)
    , _serviceID("ServiceID", D1Consts::SERVICE_ID_INVALID)
    , _code("Code", D1Consts::ID_INVALID)
    , _reason("Reason", D1Consts::ID_INVALID)
    , _carrierID("CarrierID", "")
{
}

D1MsgEventNtf::~D1MsgEventNtf()
{
}

void D1MsgEventNtf::archiveMessage(B1Archive* archive) const
{
    writeDataToArchive(_serialNumber, archive);
    writeDataToArchive(_taskID, archive);
    writeDataToArchive(_time, archive);
    writeDataToArchive(_zoneID, archive);
    writeDataToArchive(_serviceID, archive);
    writeDataToArchive(_code, archive);
    writeDataToArchive(_reason, archive);
    writeDataToArchive(_carrierID, archive);
}

void D1MsgEventNtf::unarchiveMessage(const B1Archive& archive)
{
    readDataFromArchive(archive, &_serialNumber);
    readDataFromArchive(archive, &_taskID);
    readDataFromArchive(archive, &_time);
    readDataFromArchive(archive, &_zoneID);
    readDataFromArchive(archive, &_serviceID);
    readDataFromArchive(archive, &_code);
    readDataFromArchive(archive, &_reason);
    readDataFromArchive(archive, &_carrierID);
}

B1String D1MsgEventNtf::toString() const
{
    B1String str = D1BaseMessage::toString();
    str.appendf(", serialNumber[%lld]", _serialNumber.second);
    str.appendf(", taskID[%lld]", taskID());
    str.appendf(", time[%lld]", time());
    str.appendf(", zoneID[%d]", zoneID());
    str.appendf(", serviceID[%d]", serviceID());
    str.appendf(", code[%d]", code());
    str.appendf(", reason[%d]", reason());
    str.appendf(", carrierID[%s]", carrierID().cString());
    return str;
}
