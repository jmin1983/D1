//
// D1ZoneDynamicAttributes.h
//
// Library: D1EQData
// Package: Zone
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1EQDATA_ZONE_DYNAMIC_ATTRIBUTES_H
#define _D1EQDATA_ZONE_DYNAMIC_ATTRIBUTES_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Data/D1RedisHashmapObject.h>
#include <D1EQData/D1NotifiableObject.h>

namespace BnD {
    class D1RedisClientInterface;
    class D1ZoneAttributePlugin;
    class D1ZoneDynamicAttributes : public D1NotifiableObject
                                  , public D1RedisHashmapObject {
    public:
        D1ZoneDynamicAttributes();
        D1ZoneDynamicAttributes(int32 zoneID, int32 serviceID);
        virtual ~D1ZoneDynamicAttributes();
    private:
        static bool _writeOperatorChangedLog;
    protected:
        const int32 _serviceID;
        DataInt32 _zoneID;
        D1ZoneAttributePlugin* _plugin;
    protected:
        virtual void archiveTo(B1Archive* archive) const override;
        virtual void unarchiveFrom(const B1Archive& archive) override;
    protected:
        virtual B1String redisKey() const override;
    protected:
        bool isOwnerZone() const;
        bool isWriteOperatorChangedLog() const { return _writeOperatorChangedLog; }
    public:
        D1ZoneDynamicAttributes& operator=(const D1ZoneDynamicAttributes& d)
        {
            //  _zoneID, _serviceID is immutable.
            return *this;
        }
        bool operator==(const D1ZoneDynamicAttributes& d) const
        {
            //  _serviceID is not comparable.
            return _zoneID.second == d._zoneID.second;
        }
        bool operator!=(const D1ZoneDynamicAttributes& d) const { return operator==(d) != true; }
    public:
        int32 zoneID() const { return _zoneID.second; }
        void setPlugin(D1ZoneAttributePlugin* plugin) { _plugin = plugin; }
        void reloadStates(D1RedisClientInterface* redisReader);
        void notifyAttributesChanged(D1RedisClientInterface* delayedCommander) const;
    public:
        static void setWriteOperatorChangedLog(bool flag) { _writeOperatorChangedLog = flag; }
    };
}

#endif  // !_D1EQDATA_ZONE_DYNAMIC_ATTRIBUTES_H
