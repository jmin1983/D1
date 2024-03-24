//
// D1MessageObject.cpp
//
// Library: D1Message
// Package: D1Message
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Message.h"
#include "D1MessageObject.h"

using namespace BnD;

D1MessageObject::D1MessageObject()
    : D1BaseMessage() 
    , _object()
{
}

D1MessageObject::D1MessageObject(D1BaseMessage&& baseMessage)
    : D1BaseMessage(std::move(baseMessage)) 
    , _object()
{
}

D1MessageObject::~D1MessageObject()
{
}

void D1MessageObject::archiveMessage(B1Archive* archive) const
{
    if (_object) {
        writeDataToArchive("Object", *_object, archive);
    }
}

void D1MessageObject::unarchiveMessage(const B1Archive& archive)
{
    B1Object* object = createObject();
    if (object) {
        readDataFromArchive("Object", archive, object);
    }
    _object.reset(object);
}
