//
// D1GUIMsgServiceInfosReq.cpp
//
// Library: D1Message
// Package: GUI
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Message.h"
#include "D1GUIMsgServiceInfosReq.h"

#include <D1Base/D1Consts.h>

using namespace BnD;

D1GUIMsgServiceInfosReq::D1GUIMsgServiceInfosReq()
    : D1BaseMessage()
    , _serviceIDs("ServiceIDs", std::vector<int32>())
{
    _messageID.second = messageString().copy();
}

D1GUIMsgServiceInfosReq::D1GUIMsgServiceInfosReq(D1BaseMessage&& baseMessage)
    : D1BaseMessage(std::move(baseMessage))
    , _serviceIDs("ServiceIDs", std::vector<int32>())
{
}

D1GUIMsgServiceInfosReq::~D1GUIMsgServiceInfosReq()
{
}

void D1GUIMsgServiceInfosReq::archiveMessage(B1Archive* archive) const
{
    writeDataToArchive(_serviceIDs, archive);
}

void D1GUIMsgServiceInfosReq::unarchiveMessage(const B1Archive& archive)
{
    readDataFromArchive(archive, &_serviceIDs);
}

B1String D1GUIMsgServiceInfosReq::toString() const
{
    B1String str = D1BaseMessage::toString();
    str.append(", serviceIDs");
    if (_serviceIDs.second.empty()) {
        str.append(" empty");
    }
    else {
        for (int32 serviceID : _serviceIDs.second) {
            str.appendf("[%d]", serviceID);
        }
    }
    return str;
}
