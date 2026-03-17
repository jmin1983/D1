//
// D1Unit.cpp
//
// Library: D1EQData
// Package: Unit
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1EQData.h"
#include "D1Unit.h"
#include "D1UnitRepository.h"
#include "D1UnitStateAttributes.h"

#include <D1Base/D1Consts.h>

using namespace BnD;

D1Unit::D1Unit()
    : _unitID("UnitID", D1Consts::ID_INVALID)
    , _name("Name", "")
    , _user("User", "")
    , _password("Password", "")
    , _serverAddress("ServerAddress", "")
    , _serverPort("ServerPort", 0)
{
}

D1Unit::D1Unit(int32 unitID)
    : _unitID("UnitID", unitID)
    , _name("Name", "")
    , _user("User", "")
    , _password("Password", "")
    , _serverAddress("ServerAddress", "")
    , _serverPort("ServerPort", 0)
{
}

void D1Unit::implInitializeAttributes(D1RedisClientInterface* redisReader)
{
    _stateAttributes = std::make_shared<D1UnitStateAttributes>(unitID(), redisReader);
}

void D1Unit::archiveToWithoutAttributes(B1Archive* archive) const
{
    writeDataToArchive(_unitID, archive);
    writeDataToArchive(_name, archive);
    writeDataToArchive(_user, archive);
    writeDataToArchive(_password, archive);
    writeDataToArchive(_serverAddress, archive);
    writeDataToArchive(_serverPort, archive);
}

void D1Unit::archiveTo(B1Archive* archive) const
{
    archiveToWithoutAttributes(archive);
    if (_stateAttributes) {
        writeDataToArchive("StateAttributes", *_stateAttributes, archive);
    }
}

void D1Unit::unarchiveFrom(const B1Archive& archive)
{
    readDataFromArchive(archive, &_unitID);
    readDataFromArchive(archive, &_name);
    readDataFromArchive(archive, &_user);
    readDataFromArchive(archive, &_password);
    readDataFromArchive(archive, &_serverAddress);
    readDataFromArchive(archive, &_serverPort);
    if (_stateAttributes) {
        readDataFromArchive("StateAttributes", archive, _stateAttributes.get());
    }
}

void D1Unit::makeRedisStringArgs(std::vector<B1String>* args) const
{
    setRedisString(args, _name);
    setRedisString(args, _user);
    setRedisString(args, _password);
    setRedisString(args, _serverAddress);
    setRedisString(args, _serverPort);
}

bool D1Unit::readRedisMap(const std::map<B1String, B1String>& map)
{
    readFromRedisMap(map, &_name);
    readFromRedisMap(map, &_user);
    readFromRedisMap(map, &_password);
    readFromRedisMap(map, &_serverAddress);
    readFromRedisMap(map, &_serverPort);
    return true;
}

void D1Unit::initializeAttributes(D1RedisClientInterface* redisReader)
{
    implInitializeAttributes(redisReader);
}

bool D1Unit::isAlarmed() const
{
    return _stateAttributes ? _stateAttributes->isAlarmed() : false;
}

bool D1Unit::isInService() const
{
    return _stateAttributes ? _stateAttributes->unitState() == D1UnitStateAttributes::UNIT_STATE_IN_SERVICE : false;
}

bool D1Unit::isOutOfService() const
{
    return _stateAttributes ? _stateAttributes->unitState() == D1UnitStateAttributes::UNIT_STATE_OUT_OF_SERVICE : false;
}

bool D1Unit::isOffLine() const
{
    return _stateAttributes ? _stateAttributes->unitState() == D1UnitStateAttributes::UNIT_STATE_OFFLINE : false;
}

bool D1Unit::isUnitTypeServiceSet() const
{
    return UNIT_TYPE_ID_RANGE_SERVICE_SET_MIN <= unitID() && unitID() <= UNIT_TYPE_ID_RANGE_SERVICE_SET_MAX;
}

bool D1Unit::isUnitTypeNVR() const
{
    return UNIT_TYPE_ID_RANGE_NVR_MIN <= unitID() && unitID() <= UNIT_TYPE_ID_RANGE_NVR_MAX;
}

bool D1Unit::archiveToStringWithoutAttributes(B1String* result, bool pretty) const
{
    B1Archive archive;
    archiveToWithoutAttributes(&archive);
    return archive.toString(result, pretty);
}
