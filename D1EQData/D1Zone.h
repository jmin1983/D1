//
// D1Zone.h
//
// Library: D1EQData
// Package: Zone
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1EQDATA_D1ZONE_H
#define _D1EQDATA_D1ZONE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <B1Base/B1Object.h>

#include <D1Data/D1RedisHashmapObject.h>

namespace BnD {
    class D1ZoneAttributePlugin;
    class D1ZoneOccupiedAttributes;
    class D1ZoneStateAttributes;
    class D1Zone : public B1Object
                 , public D1RedisHashmapObject {
    public:
        D1Zone();
        D1Zone(int32 D1ZoneID);
        virtual ~D1Zone() {}
    public:
        enum DIRECTION {
            DIRECTION_INVALID = -1,

            DIRECTION_NORTH = 0,
            DIRECTION_SOUTH,
            DIRECTION_WEST,
            DIRECTION_EAST,

            DIRECTION_COUNT,
        };
        enum LEVEL {
            LEVEL_INAVLID = -1,

            LEVEL_0 = 0,
            LEVEL_1,
            LEVEL_2,
        };
    private:
        DataInt32 _zoneID;
        DataString _name;
        std::pair<const B1String, LEVEL> _level;
        std::pair<const B1String, DIRECTION> _direction;
    protected:
        std::shared_ptr<D1ZoneOccupiedAttributes> _occupiedAttributes;
        std::shared_ptr<D1ZoneStateAttributes> _stateAttributes;
    protected:
        virtual void implInitializeAttributes(int32 serviceID, D1RedisClientInterface* redisReader);
        virtual void implIitializePlugins(D1ZoneAttributePlugin* attributePlugin);
    protected:
        virtual void archiveTo(B1Archive* archive) const override;
        virtual void unarchiveFrom(const B1Archive& archive) override;
    protected:
        virtual void makeRedisStringArgs(std::vector<B1String>* args) const override;
        virtual bool readRedisMap(const std::map<B1String, B1String>& map) override;
    public:
        void initializeAttributes(int32 serviceID, D1RedisClientInterface* redisReader);
        void initializePlugins(D1ZoneAttributePlugin* attributePlugin);
        int32 zoneID() const { return _zoneID.second; }
        int32 slaveID() const;
        const B1String& name() const { return _name.second; }
        LEVEL level() const { return _level.second; }
        DIRECTION direction() const { return _direction.second; }

        bool isInService() const;
        bool isOutOfService() const;
        bool isOffLine() const;

        D1ZoneOccupiedAttributes* occupiedAttributes() const { return _occupiedAttributes.get(); }
        D1ZoneStateAttributes* stateAttributes() const { return _stateAttributes.get(); }
    public:
        static bool isReverseDirection(DIRECTION l, DIRECTION r);
    };
    typedef std::shared_ptr<D1Zone> SPD1Zone;
}

#endif  // !_D1EQDATA_D1ZONE_H
