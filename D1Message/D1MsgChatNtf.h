//
// D1MsgChatNtf.h
//
// Library: D1Message
// Package: AlarmEvent
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1MESSAGE_MSG_CHAT_NTF_H
#define _D1MESSAGE_MSG_CHAT_NTF_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Message/D1BaseMessage.h>

namespace BnD {
    class D1MsgChatNtf : public D1BaseMessage {
    public:
        D1MsgChatNtf(B1String&& userFrom, B1String&& addressFrom, B1String&& messageBody);
        D1MsgChatNtf(B1String&& userTo, B1String&& userFrom, B1String&& addressFrom, B1String&& messageBody);
        D1MsgChatNtf(D1BaseMessage&& baseMessage);
        virtual ~D1MsgChatNtf();
    protected:
        DataString _userTo; //  broadcast if empty.
        DataString _userFrom;
        DataString _addressFrom;
        DataString _encodedMessageBody;
    protected:
        void archiveMessage(B1Archive* archive) const final;
        void unarchiveMessage(const B1Archive& archive) final;
    public:
        B1String toString() const final;
    public:
        const B1String& userTo() const { return _userTo.second; }
        const B1String& userFrom() const { return _userFrom.second; }
        const B1String& addressFrom() const { return _addressFrom.second; }
        const B1String& encodedMessageBody() const { return _encodedMessageBody.second; }

        void setUserTo(B1String&& value) { _userTo.second = std::move(value); }
        void setUserFrom(B1String&& value) { _userFrom.second = std::move(value); }
        void setAddressFrom(B1String&& value) { _addressFrom.second = std::move(value); }
        void setEncodedMessageBody(B1String&& value) { _encodedMessageBody.second = std::move(value); }
    public:
        static const B1String& messageString()
        {
            static B1String s_messageString("D1MsgChatNtf");
            return s_messageString;
        }
    };
}   //  !BnD

#endif  // !_D1MESSAGE_MSG_CHAT_NTF_H
