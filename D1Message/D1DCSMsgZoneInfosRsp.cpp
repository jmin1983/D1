//
// D1DCSMsgZoneInfosRsp.cpp
//
// Library: D1Message
// Package: DCS
// Module:  D1Message
//
// Copyright (c) 2023-2024, Semi-TS.
// All rights reserved.
//

#include "D1Message.h"
#include "D1DCSMsgZoneInfosRsp.h"

using namespace BnD;

D1DCSMsgZoneInfosRsp::D1DCSMsgZoneInfosRsp()
    : D1BaseMessage()
    , _zoneString("ZoneString", "")
{
    _messageID.second = messageString().copy();
}

D1DCSMsgZoneInfosRsp::D1DCSMsgZoneInfosRsp(D1BaseMessage&& baseMessage)
    : D1BaseMessage(std::move(baseMessage))
    , _zoneString("ZoneString", "")
{
}

D1DCSMsgZoneInfosRsp::~D1DCSMsgZoneInfosRsp()
{
}

void D1DCSMsgZoneInfosRsp::archiveMessage(B1Archive* archive) const
{
    writeDataToArchive(_zoneString, archive);
}

void D1DCSMsgZoneInfosRsp::unarchiveMessage(const B1Archive& archive)
{
    readDataFromArchive(archive, &_zoneString);
}

B1String D1DCSMsgZoneInfosRsp::toString() const
{
    B1String str = D1BaseMessage::toString();
    str.appendf(", zoneString[%s]", zoneString().cString());
    return str;
}
