//
// D1NotifiableObject.cpp
//
// Library: D1EQData
// Package: D1EQData
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1EQData.h"
#include "D1NotifiableObject.h"

#include <D1Message/D1MessageObject.h>

using namespace BnD;

D1NotifiableObject::D1NotifiableObject()
    : B1Object()
{
}

D1NotifiableObject::~D1NotifiableObject()
{
}

B1String D1NotifiableObject::toMessage() const
{
    std::shared_ptr<D1MessageObject> messageObject(createMessageObject());
    return messageObject->toMessage();
}
