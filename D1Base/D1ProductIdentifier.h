//
// D1ProductIdentifier.h
//
// Library: D1Base
// Package: D1Base
// Module:  D1Base
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1BASE_PRODUCT_IDENTIFIER_H
#define _D1BASE_PRODUCT_IDENTIFIER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

namespace BnD {
    class D1RedisClientInterface;
    class D1ProductIdentifier {
    public:
        D1ProductIdentifier();
        virtual ~D1ProductIdentifier();
    public:
        enum SITE {
            SITE_UNKNOWN = -1,
            SITE_STANDARD_AMHS = 0,
            SITE_STANDARD_IBSEM,
            SITE_STANDARD_STOCKERSEM,
            SITE_SOLUTION,

            SITE_COUNTS,

            SITE_RESERVED_BEGIN = 1001,
        };
        enum TYPE {
            TYPE_UNKNOWN = -1,
            TYPE_STANDARD_EQ = 0,
            TYPE_STANDARD_SERVICE,

            TYPE_COUNTS,

            TYPE_RESERVED_BEGIN = 1001,
        };
    protected:
        int32 _site;
        int32 _type;
    protected:
        static const B1String& productInfoKey();
    protected:
        virtual bool implGetProductSite(const B1String& siteString);
        virtual bool implGetProductType(const B1String& typeString);
        virtual bool implToProductSiteString(B1String* result) const;
        virtual bool implToProductTypeString(B1String* result) const;
    public:
        bool getProductInfo(D1RedisClientInterface* redisReader);
        B1String toProductSiteString() const;
        B1String toProductTypeString() const;
        B1String toString() const;
        int32 site() const { return _site; }
        int32 type() const { return _type; }
    };
}   //  !BnD

#endif  // !_D1BASE_PRODUCT_IDENTIFIER_H
