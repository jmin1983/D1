//
// D1UnitStateAttributes.h
//
// Library: D1EQData
// Package: Unit
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1EQDATA_UNIT_STATE_ATTRIBUTES_H
#define _D1EQDATA_UNIT_STATE_ATTRIBUTES_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1EQData/D1UnitDynamicAttributes.h>

namespace BnD {
    class D1UnitStateAttributes : public D1UnitDynamicAttributes {
    public:
        D1UnitStateAttributes();
        D1UnitStateAttributes(int32 unitID, D1RedisClientInterface* redisReader);
    public:
        enum UNIT_STATE {
            UNIT_STATE_UNKNOWN = -1,

            UNIT_STATE_IN_SERVICE = 0,
            UNIT_STATE_OUT_OF_SERVICE,
            UNIT_STATE_OFFLINE,
        };
    protected:
        std::pair<const B1String, UNIT_STATE> _unitState;
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
        D1UnitStateAttributes& operator=(const D1UnitStateAttributes& d);
        bool operator==(const D1UnitStateAttributes& d) const;
        bool operator!=(const D1UnitStateAttributes& d) const { return operator==(d) != true; }
    public:
        UNIT_STATE unitState() const { return static_cast<UNIT_STATE>(_unitState.second); }
        int64 alarmID() const { return _alarmID.second; }
        bool isAlarmed() const;
        bool isInService() const { return unitState() == UNIT_STATE_IN_SERVICE; }
        bool isOutOfService() const { return unitState() == UNIT_STATE_OUT_OF_SERVICE; }
        bool isOffline() const { return unitState() == UNIT_STATE_OFFLINE; }

        //  'set' is only available for ums.
        void setUnitState(UNIT_STATE state, D1RedisClientInterface* delayedCommander = NULL, bool forced = false);
        void setUnitStateValidIfUnknownState(D1RedisClientInterface* delayedCommander);
        void setUnitStateInService(D1RedisClientInterface* delayedCommander = NULL, bool forced = false) { setUnitState(UNIT_STATE_IN_SERVICE, delayedCommander, forced); }
        void setUnitStateOutOfService(D1RedisClientInterface* delayedCommander = NULL, bool forced = false) { setUnitState(UNIT_STATE_OUT_OF_SERVICE, delayedCommander, forced); }
        void setUnitStateOffline(D1RedisClientInterface* delayedCommander = NULL, bool forced = false) { setUnitState(UNIT_STATE_OFFLINE, delayedCommander, forced); }
        void setAlarmed(int64 id, D1RedisClientInterface* delayedCommander = NULL);
        void clearAlarmed(D1RedisClientInterface* delayedCommander = NULL);
    };
}

#endif  // !_D1EQDATA_UNIT_STATE_ATTRIBUTES_H
