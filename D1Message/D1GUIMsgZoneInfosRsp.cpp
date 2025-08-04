//
// D1GUIMsgZoneInfosRsp.cpp
//
// Library: D1Message
// Package: GUI
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Message.h"
#include "D1GUIMsgZoneInfosRsp.h"

using namespace BnD;

D1GUIMsgZoneInfosRsp::D1GUIMsgZoneInfosRsp()
    : D1BaseMessage()
    , _index("Index", 0)
    , _indexCount("IndexCount", 0)
    , _type("Type", TYPE_ALL)
    , _zoneStrings("ZoneStrings", std::vector<B1String>())
    , _zoneGUIDataStrings("ZoneGUIDataStrings", std::vector<B1String>())
{
    _messageID.second = messageString().copy();
}

D1GUIMsgZoneInfosRsp::D1GUIMsgZoneInfosRsp(D1BaseMessage&& baseMessage)
    : D1BaseMessage(std::move(baseMessage))
    , _index("Index", 0)
    , _indexCount("IndexCount", 0)
    , _type("Type", TYPE_ALL)
    , _zoneStrings("ZoneStrings", std::vector<B1String>())
    , _zoneGUIDataStrings("ZoneGUIDataStrings", std::vector<B1String>())
{
}

D1GUIMsgZoneInfosRsp::~D1GUIMsgZoneInfosRsp()
{
}

void D1GUIMsgZoneInfosRsp::archiveMessage(B1Archive* archive) const
{
    writeDataToArchive(_index, archive);
    writeDataToArchive(_indexCount, archive);
    writeDataToArchive(_type, archive);
    writeDataToArchive(_zoneStrings, archive);
    writeDataToArchive(_zoneGUIDataStrings, archive);
}

void D1GUIMsgZoneInfosRsp::unarchiveMessage(const B1Archive& archive)
{
    readDataFromArchive(archive, &_index);
    readDataFromArchive(archive, &_indexCount);
    readDataFromArchive(archive, &_type);
    readDataFromArchive(archive, &_zoneStrings);
    readDataFromArchive(archive, &_zoneGUIDataStrings);
}

B1String D1GUIMsgZoneInfosRsp::toString() const
{
    B1String str = D1BaseMessage::toString();
    str.appendf(", index[%d]", index());
    str.appendf(", indexCount[%d]", indexCount());
    str.appendf(", type[%d]", type());
    str.appendf(", zoneStrings_count[%d]", zoneStrings().size());
    str.appendf(", zoneGUIDataStrings_count[%d]", zoneGUIDataStrings().size());
    return str;
}
