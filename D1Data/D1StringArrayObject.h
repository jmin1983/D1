//
// D1StringArrayObject.h
//
// Library: D1Data
// Package: D1Data
// Module:  D1Data
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1DATA_STRING_ARRAY_OBJECT_H
#define _D1DATA_STRING_ARRAY_OBJECT_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <B1Base/B1Object.h>

namespace BnD {
    class D1StringArrayObject : public B1Object {
    public:
        D1StringArrayObject();
        virtual ~D1StringArrayObject();
    protected:
        std::vector<B1String> _values;
    protected:
        virtual void archiveTo(B1Archive* archive) const override;
        virtual void unarchiveFrom(const B1Archive& archive) override;
    public:
        const std::vector<B1String>& values() const { return _values; }
              std::vector<B1String>& values()       { return _values; }
    };
}   //  !BnD

#endif  // !_D1DATA_STRING_ARRAY_OBJECT_H
