//
// D1GUIMsgZoneInfosReq.cpp
//
// Library: D1Message
// Package: GUI
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Message.h"
#include "D1GUIMsgZoneInfosReq.h"

#include <D1Base/D1Consts.h>

using namespace BnD;

D1GUIMsgZoneInfosReq::D1GUIMsgZoneInfosReq()
    : D1BaseMessage()
    , _type("Type", TYPE_ALL)
    , _ownerIDs("OwnerIDs", std::vector<int32>())
{
    _messageID.second = messageString().copy();
}

D1GUIMsgZoneInfosReq::D1GUIMsgZoneInfosReq(D1BaseMessage&& baseMessage)
    : D1BaseMessage(std::move(baseMessage))
    , _type("Type", TYPE_ALL)
    , _ownerIDs("OwnerIDs", std::vector<int32>())
{
}

D1GUIMsgZoneInfosReq::~D1GUIMsgZoneInfosReq()
{
}

void D1GUIMsgZoneInfosReq::archiveMessage(B1Archive* archive) const
{
    writeDataToArchive(_type, archive);
    writeDataToArchive(_ownerIDs, archive);
}

void D1GUIMsgZoneInfosReq::unarchiveMessage(const B1Archive& archive)
{
    readDataFromArchive(archive, &_type);
    readDataFromArchive(archive, &_ownerIDs);
}

B1String D1GUIMsgZoneInfosReq::toString() const
{
    B1String str = D1BaseMessage::toString();
    str.appendf(", type[%d]", type());
    str.append(", ownerIDs");
    if (_ownerIDs.second.empty()) {
        str.append(" empty");
    }
    else {
        for (int32 ownerID : _ownerIDs.second) {
            str.appendf("[%d]", ownerID);
        }
    }
    return str;
}
