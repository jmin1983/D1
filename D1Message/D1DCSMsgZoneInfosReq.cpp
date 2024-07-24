//
// D1DCSMsgZoneInfosReq.cpp
//
// Library: D1Message
// Package: DCS
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Message.h"
#include "D1DCSMsgZoneInfosReq.h"

#include <D1Base/D1Consts.h>

using namespace BnD;

D1DCSMsgZoneInfosReq::D1DCSMsgZoneInfosReq()
    : D1BaseMessage()
    , _ownerID("OwnerID", D1Consts::SERVICE_ID_INVALID)
{
    _messageID.second = messageString().copy();
}

D1DCSMsgZoneInfosReq::D1DCSMsgZoneInfosReq(D1BaseMessage&& baseMessage)
    : D1BaseMessage(std::move(baseMessage))
    , _ownerID("OwnerID", D1Consts::SERVICE_ID_INVALID)
{
}

D1DCSMsgZoneInfosReq::~D1DCSMsgZoneInfosReq()
{
}

void D1DCSMsgZoneInfosReq::archiveMessage(B1Archive* archive) const
{
    writeDataToArchive(_ownerID, archive);
}

void D1DCSMsgZoneInfosReq::unarchiveMessage(const B1Archive& archive)
{
    readDataFromArchive(archive, &_ownerID);
}

B1String D1DCSMsgZoneInfosReq::toString() const
{
    B1String str = D1BaseMessage::toString();
    str.appendf(", ownerID[%d]", ownerID());
    return str;
}
