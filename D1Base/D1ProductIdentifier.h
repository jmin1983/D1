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
    public:
        enum SITE {
            SITE_AMHS_DEFAULT = 0,
            SITE_DIA,

            SITE_COUNTS,
            SITE_DEFAULT = SITE_AMHS_DEFAULT,
        };
        enum TYPE {
            TYPE_STANDARD_EQ = 0,
            TYPE_STANDARD_SERVICE,

            TYPE_COUNTS,
            TYPE_DEFAULT = TYPE_STANDARD_EQ,
        };
    protected:
        SITE _site;
        TYPE _type;
    public:
        SITE site() const { return _site; }
        TYPE type() const { return _type; }

        void initialize(SITE site, TYPE type);
        B1String toString() const;

        static const B1String& productInfoKey();
        static SITE getProductSite(D1RedisClientInterface* redisReader);
        static TYPE getProductType(D1RedisClientInterface* redisReader);
        static B1String toProductSiteString(SITE site);
        static B1String toProductTypeString(TYPE type);
    };
}   //  !BnD

#endif  // !_D1BASE_PRODUCT_IDENTIFIER_H
