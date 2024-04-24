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
    : _site(SITE_UNKNOWN)
    , _type(TYPE_UNKNOWN)
{
}

D1ProductIdentifier::~D1ProductIdentifier()
{
}

const B1String& D1ProductIdentifier::productInfoKey()
{
    static const B1String s_productInfoKey("System:ProductInfo");
    return s_productInfoKey;
}

bool D1ProductIdentifier::implGetProductSite(const B1String& siteString)
{
    int32 site = SITE_UNKNOWN;
    try {
        site = siteString.toInt32();
    }
    catch (...) {}
    if (site < 0 || site >= SITE_COUNTS) {
        return false;
    }
    _site = site;
    return true;
}

bool D1ProductIdentifier::implGetProductType(const B1String& typeString)
{
    int32 type = TYPE_UNKNOWN;
    try {
        type = typeString.toInt32();
    }
    catch (...) {}
    if (type < 0 || type >= TYPE_COUNTS) {
        return false;
    }
    _type = type;
    return true;
}

bool D1ProductIdentifier::implToProductSiteString(B1String* result) const
{
    switch (_site) {
        case SITE_STANDARD_AMHS:
            *result = "Standard AMHS";
            return true;
        case SITE_STANDARD_IBSEM:
            *result = "Standard IB SEM";
            return true;
        case SITE_STANDARD_STOCKERSEM:
            *result = "Standard STOCKER SEM";
            return true;
        case SITE_SOLUTION:
            *result = "Solution";
            return true;
        default:
            break;
    }
    return false;
}

bool D1ProductIdentifier::implToProductTypeString(B1String* result) const
{
    switch (_type) {
        case TYPE_STANDARD_EQ:
            *result = "Standard Equipment";
            return true;
        case TYPE_STANDARD_SERVICE:
            *result = "Standard Service";
            return true;
        default:
            break;
    }
    return false;
}

bool D1ProductIdentifier::getProductInfo(D1RedisClientInterface* redisReader)
{
    return implGetProductSite(redisReader->hmget(productInfoKey(), "Site")) && implGetProductType(redisReader->hmget(productInfoKey().copy(), "Type"));
}

B1String D1ProductIdentifier::toProductSiteString() const
{
    B1String siteString;
    if (implToProductSiteString(&siteString) != true) {
        return B1String::formatAs("UNKNOWN[%d]", _site);
    }
    else {
        return siteString;
    }
}

B1String D1ProductIdentifier::toProductTypeString() const
{
    B1String typeString;
    if (implToProductTypeString(&typeString) != true) {
        return B1String::formatAs("UNKNOWN[%d]", _type);
    }
    else {
        return typeString;
    }
}

B1String D1ProductIdentifier::toString() const
{
    return B1String::formatAs("Product: site[%s], type[%s]", toProductSiteString().cString(), toProductTypeString().cString());
}
