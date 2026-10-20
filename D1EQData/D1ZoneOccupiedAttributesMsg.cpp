//
// D1ZoneOccupiedAttributesMsg.cpp
//
// Library: D1EQData
// Package: Zone
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1EQData.h"

#include <B1Base/B1Time.h>

#include "D1ZoneOccupiedAttributesMsg.h"
#include "D1ZoneOccupiedAttributes.h"

using namespace BnD;

D1ZoneOccupiedAttributesMsg::D1ZoneOccupiedAttributesMsg(const D1ZoneOccupiedAttributes* objectToArchive)
    : D1MessageObject(objectToArchive)
{
    _messageID.second = messageString().copy();
    B1Time::getCurrentTime(&_baseTime.second, &_baseMicrosecond.second);
}

D1ZoneOccupiedAttributesMsg::D1ZoneOccupiedAttributesMsg(D1BaseMessage&& baseMessage)
    : D1MessageObject(std::move(baseMessage))
{
}

D1ZoneOccupiedAttributesMsg::~D1ZoneOccupiedAttributesMsg()
{
}

auto D1ZoneOccupiedAttributesMsg::createObject() -> std::shared_ptr<B1Object>
{
    return std::make_shared<D1ZoneOccupiedAttributes>();
}

auto D1ZoneOccupiedAttributesMsg::toObject() const -> D1ZoneOccupiedAttributes*
{
    return D1MessageObject::toObject<D1ZoneOccupiedAttributes*>();
}
