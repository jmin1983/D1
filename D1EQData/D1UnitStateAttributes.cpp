//
// D1UnitStateAttributes.cpp
//
// Library: D1EQData
// Package: Unit
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1EQData.h"
#include "D1UnitStateAttributes.h"
#include "D1UnitStateAttributesMsg.h"

#include <D1Base/D1RedisClientInterface.h>

#include <D1Base/D1Consts.h>

using namespace BnD;

D1UnitStateAttributes::D1UnitStateAttributes()
    : D1UnitDynamicAttributes()
    , _unitState("UnitState", UNIT_STATE_UNKNOWN)
    , _alarmID("AlarmID", D1Consts::ID_INVALID)
{
}

D1UnitStateAttributes::D1UnitStateAttributes(int32 unitID, D1RedisClientInterface* redisReader)
    : D1UnitDynamicAttributes(unitID)
    , _unitState("UnitState", UNIT_STATE_UNKNOWN)
    , _alarmID("AlarmID", D1Consts::ID_INVALID)
{
    if (redisReader) {
        reloadStates(redisReader);
    }
}

void D1UnitStateAttributes::archiveTo(B1Archive* archive) const
{
    D1UnitDynamicAttributes::archiveTo(archive);
    writeDataToArchive(_unitState.first, (int32)_unitState.second, archive);
    writeDataToArchive(_alarmID, archive);
}

void D1UnitStateAttributes::unarchiveFrom(const B1Archive& archive)
{
    D1UnitDynamicAttributes::unarchiveFrom(archive);
    {
        int32 state = 0;
        if (readDataFromArchive(_unitState.first, archive, &state)) {
            _unitState.second = static_cast<UNIT_STATE>(state);
        }
    }
    readDataFromArchive(archive, &_alarmID);
}

auto D1UnitStateAttributes::createMessageObject() const -> D1MessageObject*
{
    return new D1UnitStateAttributesMsg(this);
}

bool D1UnitStateAttributes::isValidToMakeRedisString() const
{
    return unitState() != UNIT_STATE_UNKNOWN;
}

void D1UnitStateAttributes::makeRedisStringArgs(std::vector<B1String>* args) const
{
    if (unitState() != UNIT_STATE_UNKNOWN) {
        setRedisString(args, _unitState.first.copy(), (int32)_unitState.second);
    }
    setRedisString(args, _alarmID);
}

bool D1UnitStateAttributes::readRedisMap(const std::map<B1String, B1String>& map)
{
    {
        int32 state = 0;
        if (readFromRedisMap(map, _unitState.first, &state)) {
            _unitState.second = static_cast<UNIT_STATE>(state);
        }
        else {
            _unitState.second = UNIT_STATE_IN_SERVICE;
        }
    }
    readFromRedisMap(map, &_alarmID);
    return true;
}

D1UnitStateAttributes& D1UnitStateAttributes::operator=(const D1UnitStateAttributes& d)
{
    {
#define PRINT_ATTRIBUTE_MEMBER(m) tmp.appendf(", "#m"[%d->%d]", _##m.second, d._##m.second);
        B1String tmp;
        tmp.appendf("unit_state_attribute changed by operator=: unitID[%d]", unitID());
        PRINT_ATTRIBUTE_MEMBER(unitState);
        tmp.appendf("alarmSerialNumber[%lld->%lld]", _alarmID.second, d._alarmID.second);
        B1LOG(tmp.cString());
    }
    D1UnitDynamicAttributes::operator=(d);
    _unitState.second = d._unitState.second;
    _alarmID.second = d._alarmID.second;
    return *this;
}

bool D1UnitStateAttributes::operator==(const D1UnitStateAttributes& d) const
{
    if (D1UnitDynamicAttributes::operator!=(d)) {
        return false;
    }
    return _unitState.second == d._unitState.second &&
           _alarmID.second == d._alarmID.second;
}

bool D1UnitStateAttributes::isAlarmed() const
{
    return alarmID() != D1Consts::ID_INVALID;
}

void D1UnitStateAttributes::setUnitState(UNIT_STATE state, D1RedisClientInterface* delayedCommander, bool forced)
{
    if (unitState() == state) {
        return;
    }
    //  'set' is only available for ums.
    //if (isOwnerZone() != true && forced != true) {
    //    assert(false);
    //    return;
    //}
    B1LOG("setUnitState: unitID[%d], unitState[%d->%d], forced[%d]", unitID(), unitState(), state, forced ? 1 : 0);
    _unitState.second = state;
    if (delayedCommander) {
        notifyAttributesChanged(delayedCommander);
    }
}

void D1UnitStateAttributes::setUnitStateValidIfUnknownState(D1RedisClientInterface* delayedCommander)
{
    if (unitState() != UNIT_STATE_UNKNOWN) {
        return;
    }
    //  'set' is only available for ums.
    //if (isOwnerZone() != true) {
    //    assert(false);
    //    return;
    //}
    B1LOG("setUnitState valid: unitID[%d]", unitID());
    _unitState.second = UNIT_STATE_IN_SERVICE;
    if (delayedCommander) {
        notifyAttributesChanged(delayedCommander);
    }
}

void D1UnitStateAttributes::setAlarmed(int64 id, D1RedisClientInterface* delayedCommander)
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
        notifyAttributesChanged(delayedCommander, true);
    }
}

void D1UnitStateAttributes::clearAlarmed(D1RedisClientInterface* delayedCommander)
{
    if (isAlarmed() != true) {
        return;
    }
    _alarmID.second = D1Consts::ID_INVALID;
    if (delayedCommander) {
        notifyAttributesChanged(delayedCommander, true);
    }
}
