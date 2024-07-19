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
        D1MessageObject(const B1Object* objectToArchive);
        D1MessageObject(D1BaseMessage&& baseMessage);
        virtual ~D1MessageObject();
    private:
        const B1Object* _objectToArchive;
        std::shared_ptr<B1Object> _unArchivedObject;
    protected:
        virtual B1Object* createObject() = 0;
    protected:
        virtual void archiveMessage(B1Archive* archive) const override;
        virtual void unarchiveMessage(const B1Archive& archive) override;
    public:
        B1String toMessage() const;
        template <typename T> T toObject() const { return static_cast<T>(_unArchivedObject.get()); }
    };
}   //  !BnD

#endif // _D1MESSAGE_MESSAGE_OBJECT_H
