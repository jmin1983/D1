//
// D1ZoneOccupiedAttributes.cpp
//
// Library: D1EQData
// Package: Zone
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1EQData.h"
#include "D1ZoneOccupiedAttributes.h"
#include "D1ZoneOccupiedAttributesMsg.h"

#include <B1Base/B1Lock.h>
#include <B1Base/B1TickUtil.h>

#include <D1Base/D1Consts.h>

using namespace BnD;

D1ZoneOccupiedAttributes::D1ZoneOccupiedAttributes()
    : D1ZoneDynamicAttributes()
    , _lock(NULL)
    , _reserveCandidates()
    , _reservedTaskID("ReservedTaskID", D1Consts::ID_INVALID)
{
}

D1ZoneOccupiedAttributes::D1ZoneOccupiedAttributes(int32 zoneID, int32 serviceID, D1RedisClientInterface* redisReader, B1Lock* lock)
    : D1ZoneDynamicAttributes(zoneID, serviceID)
    , _lock(lock)
    , _reserveCandidates()
    , _reservedTaskID("ReservedTaskID", D1Consts::ID_INVALID)
{
    if (redisReader) {
        reloadStates(redisReader);
    }
}

void D1ZoneOccupiedAttributes::archiveTo(B1Archive* archive) const
{
    D1ZoneDynamicAttributes::archiveTo(archive);
    writeDataToArchive(_reservedTaskID.first, reservedTaskID(), archive);   //  lock_and_get reservedTaskID.
}

void D1ZoneOccupiedAttributes::unarchiveFrom(const B1Archive& archive)
{
    D1ZoneDynamicAttributes::unarchiveFrom(archive);
    readDataFromArchive(archive, &_reservedTaskID);
}

auto D1ZoneOccupiedAttributes::createMessageObject() const -> D1MessageObject*
{
    return new D1ZoneOccupiedAttributesMsg(this);
}

bool D1ZoneOccupiedAttributes::isValidToMakeRedisString() const
{
    return true;    //  _reservedTaskID is always valid.
}

void D1ZoneOccupiedAttributes::makeRedisStringArgs(std::vector<B1String>* args) const
{
    setRedisString(args, _reservedTaskID.first.copy(), reservedTaskID());   //  lock_and_get reservedTaskID.
}

bool D1ZoneOccupiedAttributes::readRedisMap(const std::map<B1String, B1String>& map)
{
    readFromRedisMap(map, &_reservedTaskID);
    return true;
}

D1ZoneOccupiedAttributes& D1ZoneOccupiedAttributes::operator=(const D1ZoneOccupiedAttributes& d)
{
    if (isWriteOperatorChangedLog()) {
#define PRINT_ATTRIBUTE_MEMBER(m) tmp.appendf(", "#m"[%d->%d]", _##m.second, d._##m.second);
        B1String tmp;
        tmp.appendf("occupied_attribute changed by operator=: zoneID[%d]", zoneID());
        PRINT_ATTRIBUTE_MEMBER(reservedTaskID);
        B1LOG(tmp.cString());
    }
    D1ZoneDynamicAttributes::operator=(d);
    _reservedTaskID.second = d._reservedTaskID.second;
    return *this;
}

bool D1ZoneOccupiedAttributes::operator==(const D1ZoneOccupiedAttributes& d) const
{
    if (D1ZoneDynamicAttributes::operator!=(d)) {
        return false;
    }
    return _reservedTaskID.second == d._reservedTaskID.second;
}

int64 D1ZoneOccupiedAttributes::reservedTaskID() const
{
    int64 reservedTaskID = D1Consts::ID_INVALID;
    if (_lock) {
        _lock->lock();
    }
    reservedTaskID = _reservedTaskID.second;
    if (_lock) {
        _lock->unlock();
    }
    return reservedTaskID;
}

bool D1ZoneOccupiedAttributes::isReserved(int64 taskID, int64* reservedTaskID) const
{
    bool noneReserved = false;
    if (_lock) {
        _lock->lock();
    }
    noneReserved = _reservedTaskID.second < 0 || _reservedTaskID.second == taskID;
    if (reservedTaskID) {
        *reservedTaskID = _reservedTaskID.second;
    }
    if (_lock) {
        _lock->unlock();
    }
    return noneReserved != true;
}

bool D1ZoneOccupiedAttributes::swapReserved(int64 taskID, D1RedisClientInterface* delayedCommander)
{
    if (isOwnerZone() != true) {
        assert(false);
        return false;
    }
    if (_lock) {
        B1LOG("BEGIN_LOCK for swap_reserve zone: taskID[%lld], zoneID[%d]", taskID, zoneID());
        _lock->lock();
    }
    if (_reservedTaskID.second != D1Consts::ID_INVALID) {
        if (_reservedTaskID.second == taskID) {
            if (_lock) {
                _lock->unlock();
                B1LOG("swap_reserve zone already reserved: taskID[%lld], zoneID[%d]", taskID, zoneID());
            }
            return true;
        }
        _reservedTaskID.second = taskID;
    }
    else {
        if (_lock) {
            _lock->unlock();
            B1LOG("swap_reserve zone failed: taskID[%lld], zoneID[%d]", taskID, zoneID());
        }
        return false;
    }
    if (delayedCommander) {
        notifyAttributesChanged(delayedCommander);
    }
    if (_lock) {
        _lock->unlock();
        B1LOG("END_LOCK for swap_reserve zone: taskID[%lld], zoneID[%d]", taskID, zoneID());
    }
    return true;
}

bool D1ZoneOccupiedAttributes::setReserved(int64 taskID, D1RedisClientInterface* delayedCommander, bool useCandidate)
{
    if (isOwnerZone() != true) {
        assert(false);
        return false;
    }
    if (_lock) {
        B1LOG("BEGIN_LOCK for reserve zone: taskID[%lld], zoneID[%d]", taskID, zoneID());
        _lock->lock();
    }
    if (_reservedTaskID.second == taskID) {
        if (_lock) {
            _lock->unlock();
            B1LOG("END_LOCK for reserve zone. already reserved: taskID[%lld], zoneID[%d]", taskID, zoneID());
        }
        return true;
    }
    if (taskID != D1Consts::ID_INVALID) {
        if (_reservedTaskID.second != D1Consts::ID_INVALID) {
            if (_lock) {
                bool addCandidate = true;
                for (auto& reserveCandidatesPair : _reserveCandidates) {
                    if (reserveCandidatesPair.first == taskID) {
                        addCandidate = false;
                        reserveCandidatesPair.second = B1TickUtil::currentTick();
                        break;
                    }
                }
                if (addCandidate && useCandidate) {
                    _reserveCandidates.push_back(std::make_pair(taskID, B1TickUtil::currentTick()));
                }
                B1String candidates;
                for (auto& reserveCandidatesPair : _reserveCandidates) {
                    candidates.format("[%d]", reserveCandidatesPair.first);
                }
                _lock->unlock();
                B1LOG("END_LOCK(fail) for reserve zone: taskID[%lld], zoneID[%d], candidates%s", taskID, zoneID(), candidates.cString());
            }
            return false;
        }
        if (_reserveCandidates.empty() != true) {
            if (taskID == _reserveCandidates.front().first) {
                _reserveCandidates.pop_front();
            }
            else {
                bool addCandidate = true;
                auto now = B1TickUtil::currentTick();
                for (auto itr = _reserveCandidates.begin(); itr != _reserveCandidates.end();) {
                    if (itr->first == taskID) {
                        addCandidate = false;
                        itr->second = now;
                        ++itr;
                    }
                    else {
                        if (B1TickUtil::diffTick(itr->second, now) > CONSTS_RESERVE_CANDIDATE_TIMEOUT) {
                            B1LOG("RESERVE_CANDIDATE_TIMEDOUT: taskID[%lld], zoneID[%d]", itr->first, zoneID());
                            itr = _reserveCandidates.erase(itr);
                        }
                        else {
                            ++itr;
                        }
                    }
                }
                if (_reserveCandidates.empty() != true) {
                    if (_reserveCandidates.front().first == taskID) {
                        _reserveCandidates.pop_front();
                    }
                    else {
                        if (addCandidate && useCandidate) {
                            _reserveCandidates.push_back(std::make_pair(taskID, now));
                        }
                        B1String candidates;
                        for (const auto& reserveCandidatesPair : _reserveCandidates) {
                            candidates.format("[%d]", reserveCandidatesPair.first);
                        }
                        _lock->unlock();
                        B1LOG("END_LOCK(fail_other_priority) for reserve zone: taskID[%lld], zoneID[%d], CANDIDATES%s", taskID, zoneID(), candidates.cString());
                        return false;
                    }
                }
            }
        }
    }
    _reservedTaskID.second = taskID;
    if (_lock) {
        _lock->unlock();
        B1LOG("END_LOCK for reserve zone: taskID[%lld], zoneID[%d]", taskID, zoneID());
    }
    if (delayedCommander) {
        notifyAttributesChanged(delayedCommander);
    }
    B1LOG("END_LOCK SAVE for reserve zone: taskID[%lld], zoneID[%d]", taskID, zoneID());
    return true;
}

bool D1ZoneOccupiedAttributes::immediateClearReserved()
{
    if (isOwnerZone()) {    //  allow only remote zones.
        assert(false);
        return false;
    }
    B1LOG("begin immediate clear_reserved for remote_zone: zoneID[%d]", zoneID());
    if (_lock) {
        _lock->lock();
    }
    if (_reservedTaskID.second == D1Consts::ID_INVALID) {
        if (_lock) {
            _lock->unlock();
        }
        B1LOG("cancel immediate clear_reserved. already not reserved: zoneID[%d]", zoneID());
        return false;
    }
    _reservedTaskID.second = D1Consts::ID_INVALID;
    if (_lock) {
        _lock->unlock();
    }
    B1LOG("end immediate clear_reserved for remote_zone: zoneID[%d]", zoneID());
    return true;
}

void D1ZoneOccupiedAttributes::clearReserved(D1RedisClientInterface* delayedCommander)
{
    setReserved(D1Consts::ID_INVALID, delayedCommander);
}
