//
// D1MsgAlarmRemoteNtf.cpp
//
// Library: D1Message
// Package: AlarmEvent
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Message.h"
#include "D1MsgAlarmRemoteNtf.h"

#include <D1Base/D1Consts.h>

using namespace BnD;

D1MsgAlarmRemoteNtf::D1MsgAlarmRemoteNtf(int64 taskID, int32 zoneID, int32 serviceID, int32 code, int32 reason)
    : D1BaseMessage()
    , _taskID("TaskID", taskID)
    , _zoneID("ZoneID", zoneID)
    , _serviceID("ServiceID", serviceID)
    , _code("Code", code)
    , _reason("Reason", reason)
{
    _messageID.second = messageString().copy();
}

D1MsgAlarmRemoteNtf::D1MsgAlarmRemoteNtf(D1BaseMessage&& baseMessage)
    : D1BaseMessage(std::move(baseMessage))
    , _taskID("TaskID", D1Consts::ID_INVALID)
    , _zoneID("ZoneID", D1Consts::ID_INVALID)
    , _serviceID("ServiceID", D1Consts::SERVICE_ID_INVALID)
    , _code("Code", D1Consts::ID_INVALID)
    , _reason("Reason", D1Consts::ID_INVALID)
{
}

D1MsgAlarmRemoteNtf::~D1MsgAlarmRemoteNtf()
{
}

void D1MsgAlarmRemoteNtf::archiveMessage(B1Archive* archive) const
{
    writeDataToArchive(_taskID, archive);
    writeDataToArchive(_zoneID, archive);
    writeDataToArchive(_serviceID, archive);
    writeDataToArchive(_code, archive);
    writeDataToArchive(_reason, archive);
}

void D1MsgAlarmRemoteNtf::unarchiveMessage(const B1Archive& archive)
{
    readDataFromArchive(archive, &_taskID);
    readDataFromArchive(archive, &_zoneID);
    readDataFromArchive(archive, &_serviceID);
    readDataFromArchive(archive, &_code);
    readDataFromArchive(archive, &_reason);
}

B1String D1MsgAlarmRemoteNtf::toString() const
{
    B1String str = D1BaseMessage::toString();
    str.appendf(", taskID[%lld]", taskID());
    str.appendf(", zoneID[%d]", zoneID());
    str.appendf(", serviceID[%d]", serviceID());
    str.appendf(", code[%d]", code());
    str.appendf(", reason[%d]", reason());
    return str;
}
