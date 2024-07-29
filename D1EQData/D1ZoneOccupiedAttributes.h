//
// D1ZoneOccupiedAttributes.h
//
// Library: D1EQData
// Package: Zone
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1EQDATA_ZONE_OCCUPIED_ATTRIBUTES_H
#define _D1EQDATA_ZONE_OCCUPIED_ATTRIBUTES_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1EQData/D1ZoneDynamicAttributes.h>

#include <list>

namespace BnD {
    class B1Lock;
    class D1ZoneOccupiedAttributes : public D1ZoneDynamicAttributes {
    public:
        D1ZoneOccupiedAttributes();
        D1ZoneOccupiedAttributes(int32 zoneID, int32 serviceID, D1RedisClientInterface* redisReader, B1Lock* lock);
    protected:
        enum CONSTS {
            CONSTS_RESERVE_CANDIDATE_TIMEOUT = 20 * 1000,
        };
    protected:
        mutable B1Lock* _lock;
        std::list<std::pair<int64, uint64> > _reserveCandidates;    //  list<pair<task_id, reserved_tick> >
        DataInt64 _reservedTaskID;
    protected:
        virtual void archiveTo(B1Archive* archive) const override;
        virtual void unarchiveFrom(const B1Archive& archive) override;
        virtual D1MessageObject* createMessageObject() const override;
    protected:
        virtual bool isValidToMakeRedisString() const override;
        virtual void makeRedisStringArgs(std::vector<B1String>* args) const override;
        virtual bool readRedisMap(const std::map<B1String, B1String>& map) override;
    public:
        D1ZoneOccupiedAttributes& operator=(const D1ZoneOccupiedAttributes& d);
        bool operator==(const D1ZoneOccupiedAttributes& d) const;
        bool operator!=(const D1ZoneOccupiedAttributes& d) const { return operator==(d) != true; }
    public:
        int64 reservedTaskID() const;
        bool isReserved(int64 taskID = -1, int64* reservedTaskID = NULL) const;

        //  'set' is only available for owner.
        bool swapReserved(int64 taskID, D1RedisClientInterface* delayedCommander = NULL);
        bool setReserved(int64 taskID, D1RedisClientInterface* delayedCommander = NULL, bool useCandidate = true);  //  return true if reserve successed.
        bool immediateClearReserved();  //  to clear reservation in advance before a reservation cancellation notification from a remote dcs.
        void clearReserved(D1RedisClientInterface* delayedCommander = NULL);
    };
}

#endif  // !_D1EQDATA_ZONE_OCCUPIED_ATTRIBUTES_H
