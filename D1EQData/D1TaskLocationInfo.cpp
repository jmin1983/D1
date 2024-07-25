//
// D1TaskLocationInfo.cpp
//
// Library: D1EQData
// Package: Task
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1EQData.h"
#include "D1TaskLocationInfo.h"
#include "D1TaskLocationInfoMsg.h"

#include <D1Base/D1Consts.h>

using namespace BnD;

D1TaskLocationInfo::D1TaskLocationInfo()
    : D1TaskInfo()
    , _currentLocation("CurrentLocation", D1Consts::ID_INVALID)
{
}

D1TaskLocationInfo::D1TaskLocationInfo(int64 taskID)
    : D1TaskInfo(taskID)
    , _currentLocation("CurrentLocation", D1Consts::ID_INVALID)
{
}

D1TaskLocationInfo::D1TaskLocationInfo(int64 taskID, int32 currentLocation)
    : D1TaskInfo(taskID)
    , _currentLocation("CurrentLocation", currentLocation)
{
}

D1TaskLocationInfo::~D1TaskLocationInfo()
{
}

void D1TaskLocationInfo::archiveTo(B1Archive* archive) const
{
    D1TaskInfo::archiveTo(archive);
    writeDataToArchive(_currentLocation, archive);
}

void D1TaskLocationInfo::unarchiveFrom(const B1Archive& archive)
{
    D1TaskInfo::unarchiveFrom(archive);
    readDataFromArchive(archive, &_currentLocation);
}

auto D1TaskLocationInfo::createMessageObject() const -> D1MessageObject*
{
    return new D1TaskLocationInfoMsg(this);
}

bool D1TaskLocationInfo::isValidToMakeRedisString() const
{
    return D1TaskInfo::isValidToMakeRedisString() && currentLocation() != D1Consts::ID_INVALID;
}

void D1TaskLocationInfo::makeRedisStringArgs(std::vector<B1String>* args) const
{
    setRedisString(args, _currentLocation);
}

bool D1TaskLocationInfo::readRedisMap(const std::map<B1String, B1String>& map)
{
    return readFromRedisMap(map, &_currentLocation);
}
