//
// D1ZoneStateAttributesMsg.cpp
//
// Library: D1EQData
// Package: Zone
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1EQData.h"
#include "D1ZoneStateAttributesMsg.h"
#include "D1ZoneStateAttributes.h"

using namespace BnD;

D1ZoneStateAttributesMsg::D1ZoneStateAttributesMsg(const D1ZoneStateAttributes* objectToArchive)
    : D1MessageObject(objectToArchive)
{
    _messageID.second = messageString().copy();
}

D1ZoneStateAttributesMsg::D1ZoneStateAttributesMsg(D1BaseMessage&& baseMessage)
    : D1MessageObject(std::move(baseMessage))
{
}

D1ZoneStateAttributesMsg::~D1ZoneStateAttributesMsg()
{
}

B1Object* D1ZoneStateAttributesMsg::createObject()
{
    return new D1ZoneStateAttributes();
}

auto D1ZoneStateAttributesMsg::toObject() const -> D1ZoneStateAttributes*
{
    return D1MessageObject::toObject<D1ZoneStateAttributes*>();
}
