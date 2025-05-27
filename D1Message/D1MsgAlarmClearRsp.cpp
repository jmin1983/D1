//
// D1MsgAlarmClearRsp.cpp
//
// Library: D1Message
// Package: AlarmEvent
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Message.h"
#include "D1MsgAlarmClearRsp.h"

#include <D1Base/D1Consts.h>

using namespace BnD;

D1MsgAlarmClearRsp::D1MsgAlarmClearRsp(int64 serialNumber, int32 serviceID, int32 zoneID, int32 code, bool alarmCleared)
    : D1BaseMessage()
    , _serialNumber("SerialNumber", serialNumber)
    , _zoneID("ZoneID", zoneID)
    , _serviceID("ServiceID", serviceID)
    , _code("Code", code)
    , _alarmCleared("AlarmCleared", alarmCleared)
{
    _messageID.second = messageString().copy();
}

D1MsgAlarmClearRsp::D1MsgAlarmClearRsp(D1BaseMessage&& baseMessage)
    : D1BaseMessage(std::move(baseMessage))
    , _serialNumber("SerialNumber", D1Consts::ID_INVALID)
    , _zoneID("ZoneID", D1Consts::ID_INVALID)
    , _serviceID("ServiceID", D1Consts::SERVICE_ID_INVALID)
    , _code("Code", 0)
    , _alarmCleared("AlarmCleared", false)
{
}

D1MsgAlarmClearRsp::~D1MsgAlarmClearRsp()
{
}

void D1MsgAlarmClearRsp::archiveMessage(B1Archive* archive) const
{
    writeDataToArchive(_serialNumber, archive);
    writeDataToArchive(_zoneID, archive);
    writeDataToArchive(_serviceID, archive);
    writeDataToArchive(_code, archive);
    writeDataToArchive(_alarmCleared, archive);
}

void D1MsgAlarmClearRsp::unarchiveMessage(const B1Archive& archive)
{
    readDataFromArchive(archive, &_serialNumber);
    readDataFromArchive(archive, &_zoneID);
    readDataFromArchive(archive, &_serviceID);
    readDataFromArchive(archive, &_code);
    readDataFromArchive(archive, &_alarmCleared);
}

B1String D1MsgAlarmClearRsp::toString() const
{
    B1String str = D1BaseMessage::toString();
    str.appendf(", serialNumber[%lld]", _serialNumber.second);
    str.appendf(", zoneID[%d]", zoneID());
    str.appendf(", serviceID[%d]", serviceID());
    str.appendf(", code[%d]", code());
    str.appendf(", alarmCleared[%d]", isAlarmCleared() ? 1 : 0);
    return str;
}
