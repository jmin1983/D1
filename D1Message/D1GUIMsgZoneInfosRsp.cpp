//
// D1GUIMsgZoneInfosRsp.cpp
//
// Library: D1Message
// Package: GUI
// Module:  D1Message
//
// Copyright (c) 2023-2024, Semi-TS.
// All rights reserved.
//

#include "D1Message.h"
#include "D1GUIMsgZoneInfosRsp.h"

using namespace BnD;

D1GUIMsgZoneInfosRsp::D1GUIMsgZoneInfosRsp()
    : D1BaseMessage()
    , _index("Index", 0)
    , _indexCount("IndexCount", 0)
    , _zoneString("ZoneString", "")
    , _zoneGUIDataString("ZoneGUIDataString", "")
{
    _messageID.second = messageString().copy();
}

D1GUIMsgZoneInfosRsp::D1GUIMsgZoneInfosRsp(D1BaseMessage&& baseMessage)
    : D1BaseMessage(std::move(baseMessage))
    , _index("Index", 0)
    , _indexCount("IndexCount", 0)
    , _zoneString("ZoneString", "")
    , _zoneGUIDataString("ZoneGUIDataString", "")
{
}

D1GUIMsgZoneInfosRsp::~D1GUIMsgZoneInfosRsp()
{
}

void D1GUIMsgZoneInfosRsp::archiveMessage(B1Archive* archive) const
{
    writeDataToArchive(_index, archive);
    writeDataToArchive(_indexCount, archive);
    writeDataToArchive(_zoneString, archive);
    writeDataToArchive(_zoneGUIDataString, archive);
}

void D1GUIMsgZoneInfosRsp::unarchiveMessage(const B1Archive& archive)
{
    readDataFromArchive(archive, &_index);
    readDataFromArchive(archive, &_indexCount);
    readDataFromArchive(archive, &_zoneString);
    readDataFromArchive(archive, &_zoneGUIDataString);
}

B1String D1GUIMsgZoneInfosRsp::toString() const
{
    B1String str = D1BaseMessage::toString();
    str.appendf(", index[%d]", index());
    str.appendf(", indexCount[%d]", indexCount());
    str.appendf(", zoneString[%s]", zoneString().cString());
    str.appendf(", zoneGUIDataString[%s]", zoneGUIDataString().cString());
    return str;
}
