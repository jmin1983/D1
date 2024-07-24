//
// D1MsgRemoteLogNtf.cpp
//
// Library: D1Message
// Package: D1Message
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Message.h"
#include "D1MsgRemoteLogNtf.h"

#include <D1Base/D1Consts.h>

using namespace BnD;

D1MsgRemoteLogNtf::D1MsgRemoteLogNtf()
    : D1BaseMessage()
    , _type("Type", TYPE_UNKNOWN)
    , _serviceID("ServiceID", D1Consts::SERVICE_ID_INVALID)
    , _taskID("TaskID", D1Consts::ID_INVALID)
    , _zoneID("ZoneID", D1Consts::ID_INVALID)
    , _comment("Comment", "")
{
    _messageID.second = messageString().copy();
}

D1MsgRemoteLogNtf::D1MsgRemoteLogNtf(D1BaseMessage&& baseMessage)
    : D1BaseMessage(std::move(baseMessage))
    , _type("Type", TYPE_UNKNOWN)
    , _serviceID("ServiceID", D1Consts::SERVICE_ID_INVALID)
    , _taskID("TaskID", D1Consts::ID_INVALID)
    , _zoneID("ZoneID", D1Consts::ID_INVALID)
    , _comment("Comment", "")
{
}

D1MsgRemoteLogNtf::~D1MsgRemoteLogNtf()
{
}

void D1MsgRemoteLogNtf::archiveMessage(B1Archive* archive) const
{
    writeDataToArchive(_type, archive);
    writeDataToArchive(_serviceID, archive);
    writeDataToArchive(_taskID, archive);
    writeDataToArchive(_zoneID, archive);
    writeDataToArchive(_comment, archive);
}

void D1MsgRemoteLogNtf::unarchiveMessage(const B1Archive& archive)
{
    readDataFromArchive(archive, &_type);
    readDataFromArchive(archive, &_serviceID);
    readDataFromArchive(archive, &_taskID);
    readDataFromArchive(archive, &_zoneID);
    readDataFromArchive(archive, &_comment);
}

void D1MsgRemoteLogNtf::set(TYPE type, int32 serviceID, int32 taskID, int32 zoneID, B1String&& comment)
{
    _type.second = type;
    _serviceID.second = serviceID;
    _taskID.second = taskID;
    _zoneID.second = zoneID;
    _comment.second = std::move(comment);
}

B1String D1MsgRemoteLogNtf::toString() const
{
    B1String str = D1BaseMessage::toString();
    str.appendf(", type[%d]", _type.second);
    str.appendf(", serviceID[%d]", serviceID());
    str.appendf(", taskID[%d]", taskID());
    str.appendf(", zoneID[%d]", zoneID());
    str.appendf(", comment[%s]", comment().cString());
    return str;
}

void D1MsgRemoteLogNtf::setDebug(int32 serviceID, int32 taskID, int32 zoneID, B1String&& comment)
{
    set(TYPE_DEBUG, serviceID, taskID, zoneID, std::move(comment));
}

void D1MsgRemoteLogNtf::setInfo(int32 serviceID, int32 taskID, int32 zoneID, B1String&& comment)
{
    set(TYPE_INFO, serviceID, taskID, zoneID, std::move(comment));
}

void D1MsgRemoteLogNtf::setError(int32 serviceID, int32 taskID, int32 zoneID, B1String&& comment)
{
    set(TYPE_ERROR, serviceID, taskID, zoneID, std::move(comment));
}
