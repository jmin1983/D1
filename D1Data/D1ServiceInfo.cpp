//
// D1ServiceInfo.cpp
//
// Library: D1Data
// Package: D1Data
// Module:  D1Data
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Data.h"
#include "D1ServiceInfo.h"

#include <D1Base/D1Consts.h>

using namespace BnD;

D1ServiceInfo::D1ServiceInfo()
    : B1Object()
    , D1RedisHashmapObject()
    , _serviceID("ServiceID", D1Consts::SERVICE_ID_INVALID)
    , _buildNum("BuildNum", 0)
    , _addresses("Addresses", "")
    , _serviceName("ServiceName", "")
    , _buildDate("BuildDate", "")
    , _startTime("StartTime", "")
    , _systemID("SystemID", "")
    , _serviceState("ServiceState", SERVICE_STATE())
{
}

D1ServiceInfo::D1ServiceInfo(int32 serviceID, B1String&& serviceName)
    : B1Object()
    , D1RedisHashmapObject()
    , _serviceID("ServiceID", serviceID)
    , _buildNum("BuildNum", 0)
    , _addresses("Addresses", "")
    , _serviceName("ServiceName", std::move(serviceName))
    , _buildDate("BuildDate", "")
    , _startTime("StartTime", "")
    , _systemID("SystemID", "")
    , _serviceState("ServiceState", SERVICE_STATE())
{
}

D1ServiceInfo::D1ServiceInfo(int32 serviceID, int32 buildNum, B1String&& addresses, B1String&& serviceName, B1String&& buildDate, B1String&& startTime, B1String&& systemID)
    : B1Object()
    , D1RedisHashmapObject()
    , _serviceID("ServiceID", D1Consts::SERVICE_ID_INVALID)
    , _buildNum("BuildNum", buildNum)
    , _addresses("Addresses", std::move(addresses))
    , _serviceName("ServiceName", std::move(serviceName))
    , _buildDate("BuildDate", std::move(buildDate))
    , _startTime("StartTime", std::move(startTime))
    , _systemID("SystemID", std::move(systemID))
    , _serviceState("ServiceState", SERVICE_STATE())
{
}

D1ServiceInfo::D1ServiceInfo(D1ServiceInfo&& r) noexcept
    : B1Object()
    , D1RedisHashmapObject()
    , _serviceID("ServiceID", r._serviceID.second)
    , _buildNum("BuildNum", r._buildNum.second)
    , _addresses("Addresses", std::move(r._addresses.second))
    , _serviceName("ServiceName", std::move(r._serviceName.second))
    , _buildDate("BuildDate", std::move(r._buildDate.second))
    , _startTime("StartTime", std::move(r._startTime.second))
    , _systemID("SystemID", std::move(r._systemID.second))
    , _serviceState("ServiceState", SERVICE_STATE())
{
}

D1ServiceInfo::~D1ServiceInfo()
{
}

D1ServiceInfo::SERVICE_STATE::SERVICE_STATE()
    : B1Object()
    , _alive("Alive", ALIVE_DEFAULT)
    , _on("On", ON_DEFAULT)
{
}

D1ServiceInfo::SERVICE_STATE::SERVICE_STATE(SERVICE_STATE&& r)
    : B1Object()
    , _alive("Alive", r._alive.second)
    , _on("On", r._on.second)
{
}

void D1ServiceInfo::SERVICE_STATE::archiveTo(B1Archive* archive) const
{
    writeDataToArchive(_alive, archive);
    writeDataToArchive(_on, archive);
}

void D1ServiceInfo::SERVICE_STATE::unarchiveFrom(const B1Archive& archive)
{
    readDataFromArchive(archive, &_alive);
    readDataFromArchive(archive, &_on);
}

B1String D1ServiceInfo::SERVICE_STATE::toString() const
{
    B1String str;
    str.format("alive[%d]", _alive.second);
    str.format(", on[%d]", _on.second);
    return str;
}

void D1ServiceInfo::archiveTo(B1Archive* archive) const
{
    writeDataToArchive(_serviceID, archive);
    writeDataToArchive(_buildNum, archive);
    writeDataToArchive(_addresses, archive);
    writeDataToArchive(_serviceName, archive);
    writeDataToArchive(_buildDate, archive);
    writeDataToArchive(_startTime, archive);
    writeDataToArchive(_systemID, archive);
    writeDataToArchive(_serviceState, archive);
}

void D1ServiceInfo::unarchiveFrom(const B1Archive& archive)
{
    readDataFromArchive(archive, &_serviceID);
    readDataFromArchive(archive, &_buildNum);
    readDataFromArchive(archive, &_addresses);
    readDataFromArchive(archive, &_serviceName);
    readDataFromArchive(archive, &_buildDate);
    readDataFromArchive(archive, &_startTime);
    readDataFromArchive(archive, &_systemID);
    readDataFromArchive(archive, &_serviceState);
}

B1String D1ServiceInfo::redisKey() const
{
    if (D1Consts::SERVICE_ID_DCS_BEGIN < serviceID() && serviceID() < D1Consts::SERVICE_ID_DCS_END) {
        return B1String::formatAs("ServiceInfo:%s:%d", serviceName().cString(), serviceID());
    }
    else {
        return "ServiceInfo:" + serviceName();
    }
}

bool D1ServiceInfo::isValidToMakeRedisString() const
{
    return serviceID() != D1Consts::SERVICE_ID_INVALID && serviceName().isEmpty() != true;
}

void D1ServiceInfo::makeRedisStringArgs(std::vector<B1String>* args) const
{
    setRedisString(args, _serviceID);
    setRedisString(args, _buildNum);
    setRedisString(args, _addresses);
    setRedisString(args, _serviceName);
    setRedisString(args, _buildDate);
    setRedisString(args, _startTime);
    setRedisString(args, _systemID);
    //_serviceState //  store_in_redis seperately.
}

bool D1ServiceInfo::readRedisMap(const std::map<B1String, B1String>& map)
{
    readFromRedisMap(map, &_serviceID);
    readFromRedisMap(map, &_buildNum);
    readFromRedisMap(map, &_addresses);
    readFromRedisMap(map, &_serviceName);
    readFromRedisMap(map, &_buildDate);
    readFromRedisMap(map, &_startTime);
    readFromRedisMap(map, &_systemID);
    //_serviceState //  store_in_redis seperately.
    return true;
}

B1String D1ServiceInfo::toString() const
{
    B1String str;
    str.format("serviceID[%d]", serviceID());
    str.appendf(", buildNum[%d]", buildNum());
    str.appendf(", addresses[%s]", addresses().cString());
    str.appendf(", serviceName[%s]", serviceName().cString());
    str.appendf(", buildDate[%s]", buildDate().cString());
    str.appendf(", startTime[%s]", startTime().cString());
    str.appendf(", systemID[%s]", systemID().cString());
    str.appendf(", serviceState[%s]", _serviceState.second.toString().cString());
    return str;
}
