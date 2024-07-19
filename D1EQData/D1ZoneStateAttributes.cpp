//
// D1ZoneStateAttributes.cpp
//
// Library: D1EQData
// Package: Zone
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1EQData.h"
#include "D1ZoneStateAttributes.h"
#include "D1ZoneStateAttributesMsg.h"

#include <D1Base/D1RedisClientInterface.h>

#include <D1Base/D1Consts.h>

using namespace BnD;

D1ZoneStateAttributes::D1ZoneStateAttributes()
    : D1ZoneDynamicAttributes()
    , _zoneState("ZoneState", ZONE_STATE_UNKNOWN)
    , _alarmID("AlarmID", D1Consts::ID_INVALID)
{
}

D1ZoneStateAttributes::D1ZoneStateAttributes(int32 zoneID, int32 serviceID, D1RedisClientInterface* redisReader)
    : D1ZoneDynamicAttributes(zoneID, serviceID)
    , _zoneState("ZoneState", ZONE_STATE_UNKNOWN)
    , _alarmID("AlarmID", D1Consts::ID_INVALID)
{
    if (redisReader) {
        reloadStates(redisReader);
    }
}

void D1ZoneStateAttributes::archiveTo(B1Archive* archive) const
{
    D1ZoneDynamicAttributes::archiveTo(archive);
    writeDataToArchive(_zoneState.first, (int32)_zoneState.second, archive);
    writeDataToArchive(_alarmID, archive);
}

void D1ZoneStateAttributes::unarchiveFrom(const B1Archive& archive)
{
    D1ZoneDynamicAttributes::unarchiveFrom(archive);
    {
        int32 state = 0;
        if (readDataFromArchive(_zoneState.first, archive, &state)) {
            _zoneState.second = static_cast<ZONE_STATE>(state);
        }
    }
    readDataFromArchive(archive, &_alarmID);
}

auto D1ZoneStateAttributes::createMessageObject() const -> D1MessageObject*
{
    return new D1ZoneStateAttributesMsg(this);
}

bool D1ZoneStateAttributes::isValidToMakeRedisString() const
{
    return zoneState() != ZONE_STATE_UNKNOWN;
}

void D1ZoneStateAttributes::makeRedisStringArgs(std::vector<B1String>* args) const
{
    if (zoneState() != ZONE_STATE_UNKNOWN) {
        setRedisString(args, _zoneState.first.copy(), (int32)_zoneState.second);
    }
    setRedisString(args, _alarmID);
}

bool D1ZoneStateAttributes::readRedisMap(const std::map<B1String, B1String>& map)
{
    {
        int32 state = 0;
        if (readFromRedisMap(map, _zoneState.first, &state)) {
            _zoneState.second = static_cast<ZONE_STATE>(state);
        }
        else {
            _zoneState.second = ZONE_STATE_IN_SERVICE;
        }
    }
    readFromRedisMap(map, &_alarmID);
    return true;
}

D1ZoneStateAttributes& D1ZoneStateAttributes::operator=(const D1ZoneStateAttributes& d)
{
    if (isWriteOperatorChangedLog()) {
#define PRINT_ATTRIBUTE_MEMBER(m) tmp.appendf(", "#m"[%d->%d]", _##m.second, d._##m.second);
        B1String tmp;
        tmp.appendf("state_attribute changed by operator=: zoneID[%d]", zoneID());
        PRINT_ATTRIBUTE_MEMBER(zoneState);
        tmp.appendf("alarmSerialNumber[%lld->%lld]", _alarmID.second, d._alarmID.second);
        B1LOG(tmp.cString());
    }
    D1ZoneDynamicAttributes::operator=(d);
    _zoneState.second = d._zoneState.second;
    _alarmID.second = d._alarmID.second;
    return *this;
}

bool D1ZoneStateAttributes::operator==(const D1ZoneStateAttributes& d) const
{
    if (D1ZoneDynamicAttributes::operator!=(d)) {
        return false;
    }
    return _zoneState.second == d._zoneState.second &&
           _alarmID.second == d._alarmID.second;
}

bool D1ZoneStateAttributes::isAlarmed() const
{
    return alarmID() != D1Consts::ID_INVALID;
}

void D1ZoneStateAttributes::setZoneState(ZONE_STATE state, D1RedisClientInterface* delayedCommander, bool forced)
{
    if (zoneState() == state) {
        return;
    }
    if (isOwnerZone() != true && forced != true) {
        assert(false);
        return;
    }
    B1LOG("setZoneState: zoneID[%d], zoneState[%d->%d], forced[%d]", zoneID(), zoneState(), state, forced ? 1 : 0);
    _zoneState.second = state;
    if (delayedCommander) {
        notifyAttributesChanged(delayedCommander);
    }
}

void D1ZoneStateAttributes::setAlarmed(int64 id, D1RedisClientInterface* delayedCommander)
{
    if (alarmID() == id) {
        return;
    }
    if (isAlarmed()) {
        assert(false);
        return;
    }
    _alarmID.second = id;
    if (delayedCommander) {
        notifyAttributesChanged(delayedCommander);
    }
}

void D1ZoneStateAttributes::clearAlarmed(D1RedisClientInterface* delayedCommander)
{
    if (isAlarmed() != true) {
        return;
    }
    _alarmID.second = D1Consts::ID_INVALID;
    if (delayedCommander) {
        notifyAttributesChanged(delayedCommander);
    }
}
