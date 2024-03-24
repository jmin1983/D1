//
// D1MSMsgKeepAliveResp.h
//
// Library: D1Message
// Package: MS
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1MESSAGE_MS_MSG_KEEP_ALIVE_RESP_H
#define _D1MESSAGE_MS_MSG_KEEP_ALIVE_RESP_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Message/D1BaseMessage.h>

namespace BnD {
    class D1MSMsgKeepAliveResp : public D1BaseMessage {
    public:
        D1MSMsgKeepAliveResp();
        D1MSMsgKeepAliveResp(D1BaseMessage&& baseMessage);
        virtual ~D1MSMsgKeepAliveResp();
    protected:
        B1String _respMessage;
    protected:
        virtual void archiveMessage(B1Archive* archive) const override;
        virtual void unarchiveMessage(const B1Archive& archive) override;
    public:
        const B1String& respMessage() const { return _respMessage; }

        void setRespMessage(B1String&& value) { _respMessage = std::move(value); }
    public:
        static const B1String& messageString()
        {
            static B1String s_messageString("D1MSMsgKeepAliveResp");
            return s_messageString;
        }
    };
}   //  !BnD

#endif // _D1MESSAGE_MS_MSG_KEEP_ALIVE_RESP_H
