//
// D1ZoneStateAttributes.h
//
// Library: D1EQData
// Package: Zone
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1EQDATA_ZONE_STATE_ATTRIBUTES_H
#define _D1EQDATA_ZONE_STATE_ATTRIBUTES_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1EQData/D1ZoneDynamicAttributes.h>

namespace BnD {
    class D1ZoneStateAttributes : public D1ZoneDynamicAttributes {
    public:
        D1ZoneStateAttributes();
        D1ZoneStateAttributes(int32 zoneID, int32 serviceID, D1RedisClientInterface* redisReader);
    public:
        enum ZONE_STATE {
            ZONE_STATE_UNKNOWN = -1,

            ZONE_STATE_IN_SERVICE = 0,
            ZONE_STATE_OUT_OF_SERVICE,
            ZONE_STATE_OFFLINE,
        };
    protected:
        std::pair<const B1String, ZONE_STATE> _zoneState;
        DataInt64 _alarmID;
    protected:
        virtual void archiveTo(B1Archive* archive) const override;
        virtual void unarchiveFrom(const B1Archive& archive) override;
        virtual D1MessageObject* createMessageObject() const override;
    protected:
        virtual bool isValidToMakeRedisString() const override;
        virtual void makeRedisStringArgs(std::vector<B1String>* args) const override;
        virtual bool readRedisMap(const std::map<B1String, B1String>& map) override;
    public:
        D1ZoneStateAttributes& operator=(const D1ZoneStateAttributes& d);
        bool operator==(const D1ZoneStateAttributes& d) const;
        bool operator!=(const D1ZoneStateAttributes& d) const { return operator==(d) != true; }
    public:
        ZONE_STATE zoneState() const { return static_cast<ZONE_STATE>(_zoneState.second); }
        int64 alarmID() const { return _alarmID.second; }
        bool isAlarmed() const;
        bool isInService() const { return zoneState() == ZONE_STATE_IN_SERVICE; }
        bool isOutOfService() const { return zoneState() == ZONE_STATE_OUT_OF_SERVICE; }
        bool isOffline() const { return zoneState() == ZONE_STATE_OFFLINE; }

        //  'set' is only available for owner dcs.
        void setZoneState(ZONE_STATE state, D1RedisClientInterface* delayedCommander = NULL, bool forced = false);
        void setZoneStateInService(D1RedisClientInterface* delayedCommander = NULL, bool forced = false) { setZoneState(ZONE_STATE_IN_SERVICE, delayedCommander, forced); }
        void setZoneStateOutOfService(D1RedisClientInterface* delayedCommander = NULL, bool forced = false) { setZoneState(ZONE_STATE_OUT_OF_SERVICE, delayedCommander, forced); }
        void setZoneStateOffline(D1RedisClientInterface* delayedCommander = NULL, bool forced = false) { setZoneState(ZONE_STATE_OFFLINE, delayedCommander, forced); }
        void setAlarmed(int64 id, D1RedisClientInterface* delayedCommander = NULL);
        void clearAlarmed(D1RedisClientInterface* delayedCommander = NULL);
    };
}

#endif  // !_D1EQDATA_ZONE_STATE_ATTRIBUTES_H
