//
// D1UnitStateAttributesMsg.h
//
// Library: D1EQData
// Package: Unit
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1EQDATA_UNIT_STATE_ATTRIBUTES_MSG_H
#define _D1EQDATA_UNIT_STATE_ATTRIBUTES_MSG_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Message/D1MessageObject.h>

namespace BnD {
    class D1UnitStateAttributes;
    class D1UnitStateAttributesMsg : public D1MessageObject {
    public:
        D1UnitStateAttributesMsg(const D1UnitStateAttributes* objectToArchive);
        D1UnitStateAttributesMsg(D1BaseMessage&& baseMessage);
        virtual ~D1UnitStateAttributesMsg();
    protected:
        virtual B1Object* createObject() override;
    public:
        D1UnitStateAttributes* toObject() const;
    public:
        static const B1String& messageString()
        {
            static B1String s_messageString("D1UnitStateAttributesMsg");
            return s_messageString;
        }
    };
}   //  !BnD

#endif // _D1EQDATA_UNIT_STATE_ATTRIBUTES_MSG_H
