//
// D1MSMsgKeepAliveRsp.h
//
// Library: D1Message
// Package: MS
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1MESSAGE_MS_MSG_KEEP_ALIVE_RSP_H
#define _D1MESSAGE_MS_MSG_KEEP_ALIVE_RSP_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Message/D1BaseMessage.h>

namespace BnD {
    class D1MSMsgKeepAliveRsp : public D1BaseMessage {
    public:
        D1MSMsgKeepAliveRsp(int32 serviceID);
        D1MSMsgKeepAliveRsp(D1BaseMessage&& baseMessage);
        virtual ~D1MSMsgKeepAliveRsp();
    protected:
        DataInt32 _serviceID;
    protected:
        void archiveMessage(B1Archive* archive) const final;
        void unarchiveMessage(const B1Archive& archive) final;
    public:
        int32 serviceID() const { return _serviceID.second; }
    public:
        static const B1String& messageString()
        {
            static B1String s_messageString("D1MSMsgKeepAliveRsp");
            return s_messageString;
        }
    };
}   //  !BnD

#endif // _D1MESSAGE_MS_MSG_KEEP_ALIVE_RSP_H
