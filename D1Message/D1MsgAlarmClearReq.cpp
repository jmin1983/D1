//
// D1MsgAlarmClearReq.cpp
//
// Library: D1Message
// Package: AlarmEvent
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Message.h"
#include "D1MsgAlarmClearReq.h"

#include <D1Base/D1Consts.h>

using namespace BnD;

D1MsgAlarmClearReq::D1MsgAlarmClearReq()
    : D1BaseMessage()
    , _serialNumber("SerialNumber", D1Consts::ID_INVALID)
    , _zoneID("ZoneID", D1Consts::ID_INVALID)
    , _resolvedBy("ResolvedBy", "")
{
    _messageID.second = messageString().copy();
}

D1MsgAlarmClearReq::D1MsgAlarmClearReq(D1BaseMessage&& baseMessage)
    : D1BaseMessage(std::move(baseMessage))
    , _serialNumber("SerialNumber", D1Consts::ID_INVALID)
    , _zoneID("ZoneID", D1Consts::ID_INVALID)
    , _resolvedBy("ResolvedBy", "")
{
}

D1MsgAlarmClearReq::~D1MsgAlarmClearReq()
{
}

void D1MsgAlarmClearReq::archiveMessage(B1Archive* archive) const
{
    writeDataToArchive(_serialNumber, archive);
    writeDataToArchive(_zoneID, archive);
    writeDataToArchive(_resolvedBy, archive);
}

void D1MsgAlarmClearReq::unarchiveMessage(const B1Archive& archive)
{
    readDataFromArchive(archive, &_serialNumber);
    readDataFromArchive(archive, &_zoneID);
    readDataFromArchive(archive, &_resolvedBy);
}

B1String D1MsgAlarmClearReq::toString() const
{
    B1String str = D1BaseMessage::toString();
    str.appendf(", serialNumber[%lld]", _serialNumber.second);
    str.appendf(", zoneID[%d]", zoneID());
    str.appendf(", resolvedBy[%s]", resolvedBy().cString());
    return str;
}
