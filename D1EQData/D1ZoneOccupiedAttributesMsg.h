//
// D1ZoneOccupiedAttributesMsg.h
//
// Library: D1EQData
// Package: Zone
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1EQDATA_ZONE_OCCUPIED_ATTRIBUTES_MSG_H
#define _D1EQDATA_ZONE_OCCUPIED_ATTRIBUTES_MSG_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Message/D1MessageObject.h>

namespace BnD {
    class D1ZoneOccupiedAttributes;
    class D1ZoneOccupiedAttributesMsg : public D1MessageObject {
    public:
        D1ZoneOccupiedAttributesMsg(const D1ZoneOccupiedAttributes* objectToArchive);
        D1ZoneOccupiedAttributesMsg(D1BaseMessage&& baseMessage);
        virtual ~D1ZoneOccupiedAttributesMsg();
    protected:
        virtual B1Object* createObject() override;
    public:
        D1ZoneOccupiedAttributes* toObject() const;
    public:
        static const B1String& messageString()
        {
            static B1String s_messageString("D1ZoneOccupiedAttributesMsg");
            return s_messageString;
        }
    };
}   //  !BnD

#endif // _D1EQDATA_ZONE_OCCUPIED_ATTRIBUTES_MSG_H
