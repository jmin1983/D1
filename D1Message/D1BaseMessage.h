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
        const static B1String _messageDataKey;  //  TODO: remove after impl pathInto, pathOut.
        DataString _messageID;
        DataString _baseTime;   //  local time.
    protected:
        virtual void archiveTo(B1Archive* archive) const override;
        virtual void unarchiveFrom(const B1Archive& archive) override;
    protected:
        virtual void archiveMessage(B1Archive* archive) const {}
        virtual void unarchiveMessage(const B1Archive& archive) {}
        virtual B1String toString() const;
    public:
        const B1String& messageID() const { return _messageID.second; }
        const B1String& baseTime() const { return _baseTime.second; }
        bool composeToJson(B1String* json) const;
        bool composeToJson(B1String* json, bool doNotSetBaseTime);
        void setBaseTime(B1String&& baseTime) { _baseTime.second = std::move(baseTime); }
    };
}   //  !BnD

#endif  // !_D1MESSAGE_BASE_MESSAGE_H
