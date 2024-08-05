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
#include "D1Consts.h"
#include "D1ProductIdentifier.h"
#include "D1RedisClientInterface.h"

using namespace BnD;
using namespace D1Consts;

D1ProductIdentifier::D1ProductIdentifier(SERVICE_ID serviceID)
    : _site(SITE_UNKNOWN)
    , _type(TYPE_UNKNOWN)
    , _serviceID(serviceID)
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

B1String D1ProductIdentifier::serviceNameCCS() const
{
    return "CCS";
}

B1String D1ProductIdentifier::serviceNameCUS() const
{
    return "CUS";
}

B1String D1ProductIdentifier::serviceNameCSS() const
{
    return "CSS";
}

B1String D1ProductIdentifier::serviceNameDWS() const
{
    return "DWS";
}

B1String D1ProductIdentifier::serviceNameDCS() const
{
    return "DCS";
}

B1String D1ProductIdentifier::serviceNameDSS() const
{
    return "DSS";
}

B1String D1ProductIdentifier::serviceNameDUS() const
{
    return "DUS";
}

B1String D1ProductIdentifier::serviceNameECS() const
{
    return "ECS";
}

B1String D1ProductIdentifier::serviceNameMS() const
{
    return "MS";
}

B1String D1ProductIdentifier::serviceNameRS() const
{
    return "RS";
}

B1String D1ProductIdentifier::serviceNameWAS() const
{
    return "WAS";
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

B1String D1ProductIdentifier::serviceName() const
{
    return serviceNameByID(_serviceID);
}

B1String D1ProductIdentifier::serviceNameByID(int32 serviceID) const
{
    if (SERVICE_ID_DCS_BEGIN < serviceID && serviceID < SERVICE_ID_DCS_END) {
        return serviceNameDCS();
    }
    if (SERVICE_ID_DUS_BEGIN < serviceID && serviceID < SERVICE_ID_DUS_END) {
        return serviceNameDUS();
    }
    if (SERVICE_ID_DSS_BEGIN < serviceID && serviceID < SERVICE_ID_DSS_END) {
        return serviceNameDSS();
    }
    switch (serviceID) {
        case SERVICE_ID_CCS:
            return serviceNameCCS();
        case SERVICE_ID_CUS:
            return serviceNameCUS();
        case SERVICE_ID_CSS:
            return serviceNameCSS();
        case SERVICE_ID_MS:
            return serviceNameMS();
        case SERVICE_ID_ECS:
            return serviceNameECS();
        case SERVICE_ID_DWS:
            return serviceNameDWS();
        case SERVICE_ID_WAS:
            return serviceNameWAS();
        case SERVICE_ID_RS:
            return serviceNameRS();
        default:
            break;

    }
    return "NA";
}

B1String D1ProductIdentifier::toString() const
{
    return B1String::formatAs("Product: site[%s], type[%s]", toProductSiteString().cString(), toProductTypeString().cString());
}
