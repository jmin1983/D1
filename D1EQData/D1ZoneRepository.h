//
// D1ZoneRepository.h
//
// Library: D1EQData
// Package: Zone
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1EQDATA_ZONE_REPOSITORY_H
#define _D1EQDATA_ZONE_REPOSITORY_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1EQData/D1Zone.h>

#include <map>
#include <set>
#include <list>

namespace BnD {
    class D1ZoneRepository {
    public:
        D1ZoneRepository() {}
        virtual ~D1ZoneRepository() {}
    protected:
        enum CONSTS {
            CONSTS_MAX_SLAVE_ID = 10000,
        };
    protected:
        std::map<int32, std::map<int32, SPD1Zone> > _zones; //  map<owner_id, map<zone_id, zone> >
    protected:
        virtual bool implInitialize() { return true; }
        virtual void implFinalize() {}
    public:
        bool initialize(const std::map<int32, SPD1Zone>& zoneInfos);    //  map<zone_id, zone>
        bool initialize(const std::list<SPD1Zone>& zones);
        void finalize();
        void initializePlugin(int32 ownerID, D1ZoneAttributePlugin* plugin);
        SPD1Zone findZone(int32 zoneID) const;

        const std::map<int32, std::map<int32, SPD1Zone> >& allZones() const { return _zones; }
        std::set<int32> ownerIDs(const std::set<int32>& exceptOwner = std::set<int32>()) const; //  all owner if except_owner is empty
        std::map<int32, SPD1Zone> zones(int32 ownerID) const;
        std::map<int32, SPD1Zone> zonesNotOwned(int32 ownerID) const;
    public:
        static int32 toSlaveID(int32 zoneID);
        static int32 toOwnerID(int32 zoneID);
        static bool isOwnerZone(int32 zoneID, int32 ownerID);
    };
}

#endif  // !_D1EQDATA_ZONE_REPOSITORY_H
