//
// D1UnitStateAttributesMsg.cpp
//
// Library: D1EQData
// Package: Unit
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1EQData.h"
#include "D1UnitStateAttributesMsg.h"
#include "D1UnitStateAttributes.h"

using namespace BnD;

D1UnitStateAttributesMsg::D1UnitStateAttributesMsg(const D1UnitStateAttributes* objectToArchive)
    : D1MessageObject(objectToArchive)
{
    _messageID.second = messageString().copy();
}

D1UnitStateAttributesMsg::D1UnitStateAttributesMsg(D1BaseMessage&& baseMessage)
    : D1MessageObject(std::move(baseMessage))
{
}

D1UnitStateAttributesMsg::~D1UnitStateAttributesMsg()
{
}

B1Object* D1UnitStateAttributesMsg::createObject()
{
    return new D1UnitStateAttributes();
}

auto D1UnitStateAttributesMsg::toObject() const -> D1UnitStateAttributes*
{
    return D1MessageObject::toObject<D1UnitStateAttributes*>();
}
