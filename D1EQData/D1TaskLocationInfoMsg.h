//
// D1TaskLocationInfoMsg.h
//
// Library: D1EQData
// Package: Task
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1EQDATA_TASK_LOCATION_INFO_MSG_H
#define _D1EQDATA_TASK_LOCATION_INFO_MSG_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Message/D1MessageObject.h>

namespace BnD {
    class D1TaskLocationInfo;
    class D1TaskLocationInfoMsg : public D1MessageObject {
    public:
        D1TaskLocationInfoMsg(const D1TaskLocationInfo* objectToArchive);
        D1TaskLocationInfoMsg(D1BaseMessage&& baseMessage);
        virtual ~D1TaskLocationInfoMsg();
    protected:
        virtual B1Object* createObject() override;
    public:
        D1TaskLocationInfo* toObject() const;
    public:
        static const B1String& messageString()
        {
            static B1String s_messageString("D1TaskLocationInfoMsg");
            return s_messageString;
        }
    };
}   //  !BnD

#endif // _D1EQDATA_TASK_LOCATION_INFO_MSG_H
