//
// D1TaskLocationInfoMsg.cpp
//
// Library: D1EQData
// Package: Task
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1EQData.h"
#include "D1TaskLocationInfoMsg.h"
#include "D1TaskLocationInfo.h"

using namespace BnD;

D1TaskLocationInfoMsg::D1TaskLocationInfoMsg(const D1TaskLocationInfo* objectToArchive)
    : D1MessageObject(objectToArchive)
{
    _messageID.second = messageString().copy();
}

D1TaskLocationInfoMsg::D1TaskLocationInfoMsg(D1BaseMessage&& baseMessage)
    : D1MessageObject(std::move(baseMessage))
{
}

D1TaskLocationInfoMsg::~D1TaskLocationInfoMsg()
{
}

B1Object* D1TaskLocationInfoMsg::createObject()
{
    return new D1TaskLocationInfo();
}

auto D1TaskLocationInfoMsg::toObject() const -> D1TaskLocationInfo*
{
    return D1MessageObject::toObject<D1TaskLocationInfo*>();
}
