//
// D1MSMsgKeepAliveReq.h
//
// Library: D1Message
// Package: MS
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1MESSAGE_MS_MSG_KEEP_ALIVE_REQ_H
#define _D1MESSAGE_MS_MSG_KEEP_ALIVE_REQ_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Message/D1BaseMessage.h>

namespace BnD {
    class D1MSMsgKeepAliveReq : public D1BaseMessage {
    public:
        D1MSMsgKeepAliveReq();
        D1MSMsgKeepAliveReq(D1BaseMessage&& baseMessage);
        virtual ~D1MSMsgKeepAliveReq();
    public:
        static const B1String& messageString()
        {
            static B1String s_messageString("D1MSMsgKeepAliveReq");
            return s_messageString;
        }
    };
}   //  !BnD

#endif // _D1MESSAGE_MS_MSG_KEEP_ALIVE_REQ_H
