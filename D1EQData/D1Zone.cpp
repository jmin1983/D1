//
// D1Zone.cpp
//
// Library: D1EQData
// Package: Zone
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1EQData.h"
#include "D1Zone.h"
#include "D1ZoneOccupiedAttributes.h"
#include "D1ZoneRepository.h"
#include "D1ZoneStateAttributes.h"

#include <D1Base/D1Consts.h>

using namespace BnD;

D1Zone::D1Zone()
    : _zoneID("ZoneID", D1Consts::ID_INVALID)
    , _name("Name", "")
    , _level("Level", LEVEL_INAVLID)
    , _direction("Direction", DIRECTION_INVALID)
    , _occupiedAttributes()
    , _stateAttributes()
{
}

D1Zone::D1Zone(int32 D1ZoneID)
    : _zoneID("ZoneID", D1ZoneID)
    , _name("Name", "")
    , _level("Level", LEVEL_INAVLID)
    , _direction("Direction", DIRECTION_INVALID)
    , _occupiedAttributes()
    , _stateAttributes()
{
}

void D1Zone::implInitializeAttributes(int32 serviceID, D1RedisClientInterface* redisReader, bool loadFromRedisAllData)
{
    _occupiedAttributes.reset(new D1ZoneOccupiedAttributes(zoneID(), serviceID, redisReader, NULL));
    _stateAttributes.reset(new D1ZoneStateAttributes(zoneID(), serviceID, redisReader));
}

void D1Zone::implIitializePlugins(D1ZoneAttributePlugin* attributePlugin)
{
    if (_occupiedAttributes) {
        _occupiedAttributes->setPlugin(attributePlugin);
    }
    if (_stateAttributes) {
        _stateAttributes->setPlugin(attributePlugin);
    }
}

void D1Zone::archiveTo(B1Archive* archive) const
{
    writeDataToArchive(_zoneID, archive);
    writeDataToArchive(_name, archive);
    writeDataToArchive(_level.first, (int32)_level.second, archive);
    writeDataToArchive(_direction.first, (int32)_direction.second, archive);
    if (_occupiedAttributes) {
        writeDataToArchive("OccupiedAttributes", *_occupiedAttributes, archive);
    }
    if (_stateAttributes) {
        writeDataToArchive("StateAttributes", *_stateAttributes, archive);
    }
}

void D1Zone::unarchiveFrom(const B1Archive& archive)
{
    readDataFromArchive(archive, &_zoneID);
    readDataFromArchive(archive, &_name);
    {
        int32 level = 0;
        if (readDataFromArchive(_level.first, archive, &level)) {
            _level.second = (LEVEL)level;
        }
    }
    {
        int32 direction = 0;
        if (readDataFromArchive(_direction.first, archive, &direction)) {
            _direction.second = (DIRECTION)direction;
        }
    }
    if (_occupiedAttributes) {
        readDataFromArchive("OccupiedAttributes", archive, _occupiedAttributes.get());
    }
    if (_stateAttributes) {
        readDataFromArchive("StateAttributes", archive, _stateAttributes.get());
    }
}

void D1Zone::makeRedisStringArgs(std::vector<B1String>* args) const
{
    setRedisString(args, _name);
    setRedisString(args, _level.first.copy(), (int32)_level.second);
    setRedisString(args, _direction.first.copy(), (int32)_direction.second);
}

bool D1Zone::readRedisMap(const std::map<B1String, B1String>& map)
{
    readFromRedisMap(map, &_name);
    {
        int32 level = 0;
        if (readFromRedisMap(map, _level.first, &level)) {
            _level.second = static_cast<LEVEL>(level);
        }
    }
    {
        int32 direction = 0;
        if (readFromRedisMap(map, _direction.first, &direction)) {
            _direction.second = static_cast<DIRECTION>(direction);
        }
    }
    return true;
}

void D1Zone::initializeAttributes(int32 serviceID, D1RedisClientInterface* redisReader, bool loadFromRedisAllData)
{
    implInitializeAttributes(serviceID, redisReader, loadFromRedisAllData);
}

void D1Zone::initializePlugins(D1ZoneAttributePlugin* attributePlugin)
{
    implIitializePlugins(attributePlugin);
}

int32 D1Zone::slaveID() const
{
    assert(zoneID() != D1Consts::ID_INVALID);
    return D1ZoneRepository::toSlaveID(zoneID());
}

int64 D1Zone::reservedTaskID() const
{
    return _occupiedAttributes ? _occupiedAttributes->reservedTaskID() : D1Consts::ID_INVALID;
}

bool D1Zone::isReserved(int64 taskID, int64* reservedTaskID) const
{
    return _occupiedAttributes ? _occupiedAttributes->isReserved(taskID, reservedTaskID) : false;
}

bool D1Zone::isAlarmed() const
{
    return _stateAttributes ? _stateAttributes->isAlarmed() : false;
}

bool D1Zone::isInService() const
{
    return _stateAttributes ? _stateAttributes->zoneState() == D1ZoneStateAttributes::ZONE_STATE_IN_SERVICE : false;
}

bool D1Zone::isOutOfService() const
{
    return _stateAttributes ? _stateAttributes->zoneState() == D1ZoneStateAttributes::ZONE_STATE_OUT_OF_SERVICE : false;
}

bool D1Zone::isOffLine() const
{
    return _stateAttributes ? _stateAttributes->zoneState() == D1ZoneStateAttributes::ZONE_STATE_OFFLINE : false;
}

bool D1Zone::isReverseDirection(DIRECTION l, DIRECTION r)
{
    switch (l) {
        case DIRECTION_NORTH:
            return DIRECTION_SOUTH == r;
        case DIRECTION_SOUTH:
            return DIRECTION_NORTH == r;
        case DIRECTION_WEST:
            return DIRECTION_EAST == r;
        case DIRECTION_EAST:
            return DIRECTION_WEST == r;
        default:
            break;
    }
    return false;
}
