//
// D1NotifiableObject.h
//
// Library: D1EQData
// Package: D1EQData
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1EQDATA_NOTIFIABLE_OBJECT_H
#define _D1EQDATA_NOTIFIABLE_OBJECT_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <B1Base/B1Object.h>

namespace BnD {
    class D1MessageObject;
    class D1NotifiableObject : public B1Object {
    public:
        D1NotifiableObject();
        virtual ~D1NotifiableObject();
    protected:
        virtual D1MessageObject* createMessageObject() const = 0;
    public:
        B1String toMessage() const;
    };
}

#endif  // !_D1EQDATA_NOTIFIABLE_OBJECT_H
