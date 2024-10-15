//
// D1ZoneAttributePlugin.h
//
// Library: D1EQData
// Package: Zone
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1EQDATA_ZONE_ATTRIBUTE_PLUGIN_H
#define _D1EQDATA_ZONE_ATTRIBUTE_PLUGIN_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

namespace BnD {
    class D1ZoneAttributePlugin {
    public:
        virtual ~D1ZoneAttributePlugin() {}
    public:
        virtual void implNotifyAttributesChanged(int32 zoneID, const B1String& message, bool costAffectable) {}
    };
}   //  !BnD

#endif  // !_D1EQDATA_ZONE_ATTRIBUTE_PLUGIN_H
