//
// D1BaseMessage.h
//
// Library: D1Message
// Package: D1Message
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1MESSAGE_BASE_MESSAGE_H
#define _D1MESSAGE_BASE_MESSAGE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <B1Base/B1Object.h>

namespace BnD {
    class D1BaseMessage : public B1Object {
    public:
        D1BaseMessage();
        D1BaseMessage(D1BaseMessage&& base) noexcept;
        virtual ~D1BaseMessage();
    protected:
        const static B1String _messageDataKey;
        DataString _messageID;
        DataInt64 _baseTime;    //  local time(second).
    protected:
        void archiveTo(B1Archive* archive) const final;
        void unarchiveFrom(const B1Archive& archive) final;
    protected:
        virtual void archiveMessage(B1Archive* archive) const {}
        virtual void unarchiveMessage(const B1Archive& archive) {}
    public:
        virtual B1String toString() const;
    public:
        const B1String& messageID() const { return _messageID.second; }
        int64 baseTime() const { return _baseTime.second; }
        bool composeToJson(B1String* json) const;
        bool composeToJsonWithBaseTime(B1String* json);
        void setBaseTime(int64 baseTime) { _baseTime.second = baseTime; }
    };
}   //  !BnD

#endif  // !_D1MESSAGE_BASE_MESSAGE_H
