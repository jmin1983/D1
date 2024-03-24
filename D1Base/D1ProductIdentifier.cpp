//
// D1ProductIdentifier.cpp
//
// Library: D1Base
// Package: D1Base
// Module:  D1Base
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Base.h"
#include "D1ProductIdentifier.h"
#include "D1RedisClientInterface.h"

using namespace BnD;

D1ProductIdentifier::D1ProductIdentifier()
    : _site(SITE_DEFAULT)
    , _type(TYPE_DEFAULT)
{
}

void D1ProductIdentifier::initialize(SITE site, TYPE type)
{
    _site = site;
    _type = type;
}

B1String D1ProductIdentifier::toString() const
{
    B1String str("Equipment: ");
    switch (_site) {
        case SITE_AMHS_DEFAULT:
            str.appendf(", site: AMHS");
            break;
        case SITE_DIA:
            str.appendf(", site: DIA");
            break;
        default:
            str.appendf(", site: UNKNOWN[%d]", _site);
            break;
    }
    switch (_type) {
        case TYPE_HOIST:
            str.appendf(", type: Hoist");
            break;
        case TYPE_STANDARD_SERVICE:
            str.appendf(", type: Standard Service");
            break;
        default:
            str.appendf(", type: UNKNOWN[%d]", _type);
            break;
    }
    return str;
}

const B1String& D1ProductIdentifier::productInfoKey()
{
    static const B1String s_productInfoKey("System:ProductInfo");
    return s_productInfoKey;
}

D1ProductIdentifier::SITE D1ProductIdentifier::getProductSite(D1RedisClientInterface* redisReader)
{


    const B1String siteString = redisReader->hmget(productInfoKey().copy(), "Site");




    int32 site = SITE_DEFAULT;
    try {
        site = siteString.toInt32();
    }
    catch (...) {}
    if (site < 0 || site > SITE_COUNTS) {
        assert(false);
        site = SITE_DEFAULT;
    }
    return static_cast<SITE>(site);
}

D1ProductIdentifier::TYPE D1ProductIdentifier::getProductType(D1RedisClientInterface* redisReader)
{


    const B1String eqTypeString = redisReader->hmget(productInfoKey().copy(), "Type");




    int32 type = TYPE_DEFAULT;
    try {
        type = eqTypeString.toInt32();
    }
    catch (...) {}
    if (type < 0 || type > TYPE_COUNTS) {
        assert(false);
        type = TYPE_DEFAULT;
    }
    return static_cast<TYPE>(type);
}

B1String D1ProductIdentifier::toProductSiteString(SITE site)
{
    switch (site) {
        case SITE_AMHS_DEFAULT:
            return "AMHS";
        default:
            break;
    }
    return B1String::formatAs("UNKNOWN[%d]", site);
}

B1String D1ProductIdentifier::toProductTypeString(TYPE type)
{
    switch (type) {
        case TYPE_HOIST:
            return "Hoist";
        default:
            break;
    }
    return B1String::formatAs("UNKNOWN[%d]", type);
}
