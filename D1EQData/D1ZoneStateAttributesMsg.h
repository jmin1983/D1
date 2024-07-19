//
// D1ZoneStateAttributesMsg.h
//
// Library: D1EQData
// Package: Zone
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1EQDATA_ZONE_STATE_ATTRIBUTES_MSG_H
#define _D1EQDATA_ZONE_STATE_ATTRIBUTES_MSG_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Message/D1MessageObject.h>

namespace BnD {
    class D1ZoneStateAttributes;
    class D1ZoneStateAttributesMsg : public D1MessageObject {
    public:
        D1ZoneStateAttributesMsg(const D1ZoneStateAttributes* objectToArchive);
        D1ZoneStateAttributesMsg(D1BaseMessage&& baseMessage);
        virtual ~D1ZoneStateAttributesMsg();
    protected:
        virtual B1Object* createObject() override;
    public:
        D1ZoneStateAttributes* toObject() const;
    public:
        static const B1String& messageString()
        {
            static B1String s_messageString("D1ZoneStateAttributesMsg");
            return s_messageString;
        }
    };
}   //  !BnD

#endif // _D1EQDATA_ZONE_STATE_ATTRIBUTES_MSG_H
