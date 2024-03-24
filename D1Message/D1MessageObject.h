//
// D1MessageObject.h
//
// Library: D1Message
// Package: D1Message
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1MESSAGE_MESSAGE_OBJECT_H
#define _D1MESSAGE_MESSAGE_OBJECT_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Message/D1BaseMessage.h>

namespace BnD {
    class D1MessageObject : public D1BaseMessage {
    public:
        D1MessageObject();
        D1MessageObject(D1BaseMessage&& baseMessage);
        virtual ~D1MessageObject();
    protected:
        std::shared_ptr<B1Object> _object;
    protected:
        virtual B1Object* createObject() = 0;
    protected:
        virtual void archiveMessage(B1Archive* archive) const override;
        virtual void unarchiveMessage(const B1Archive& archive) override;
    public:
        template <typename T> T getObject() const { return static_cast<T>(_object.get()); }

        void setObject(std::shared_ptr<B1Object> object) { _object = object; }
    };
}   //  !BnD

#endif // _D1MESSAGE_MESSAGE_OBJECT_H
