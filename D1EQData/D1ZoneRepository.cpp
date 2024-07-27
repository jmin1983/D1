//
// D1ZoneRepository.cpp
//
// Library: D1EQData
// Package: Zone
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1EQData.h"
#include "D1ZoneRepository.h"

using namespace BnD;

bool D1ZoneRepository::initialize(const std::map<int32, SPD1Zone>& zoneInfos)
{
    if (_zones.empty() != true) {
        return false;
    }
    for (const auto& zoneInfosPair : zoneInfos) {
        const auto& zone = zoneInfosPair.second;
        _zones[toOwnerID(zone->zoneID())][zone->zoneID()] = zone;
    }
    return implInitialize();
}

bool D1ZoneRepository::initialize(const std::list<SPD1Zone>& zones)
{
    if (_zones.empty() != true) {
        return false;
    }
    for (const auto& zone : zones) {
        _zones[toOwnerID(zone->zoneID())][zone->zoneID()] = zone;
    }
    return implInitialize();
}

void D1ZoneRepository::finalize()
{
    implFinalize();
    _zones.clear();
}

void D1ZoneRepository::initializePlugin(int32 ownerID, D1ZoneAttributePlugin* plugin)
{
    auto ownerZones = zones(ownerID);
    for (const auto& ownerZonesPair : ownerZones) {
        ownerZonesPair.second->initializePlugins(plugin);
    }
}

SPD1Zone D1ZoneRepository::findZone(int32 zoneID) const
{
    int32 ownerID = toOwnerID(zoneID);
    auto itr = _zones.find(ownerID);
    if (itr == _zones.end()) {
        return SPD1Zone();
    }
    auto jtr = itr->second.find(zoneID);
    return jtr != itr->second.end() ? jtr->second : SPD1Zone();
}

auto D1ZoneRepository::ownerIDs(const std::set<int32>& exceptOwner) const -> std::set<int32>
{
    std::set<int32> ids;
    for (const auto& zonesPair : _zones) {
        if (exceptOwner.empty() || exceptOwner.find(zonesPair.first) == exceptOwner.end()) {
            ids.insert(zonesPair.first);
        }
    }
    return ids;
}

auto D1ZoneRepository::zones(int32 ownerID) const -> std::map<int32, SPD1Zone>
{
    auto itr = _zones.find(ownerID);
    return itr != _zones.end() ? itr->second : std::map<int32, SPD1Zone>();
}

auto D1ZoneRepository::zonesNotOwned(int32 ownerID) const -> std::map<int32, SPD1Zone>
{
    std::map<int32, SPD1Zone> result;
    for (const auto& zonesPair : _zones) {
        if (zonesPair.first != ownerID) {
            result.insert(zonesPair.second.begin(), zonesPair.second.end());
        }
    }
    return result;
}

int32 D1ZoneRepository::toSlaveID(int32 zoneID)
{
    return zoneID % CONSTS_MAX_SLAVE_ID;
}

int32 D1ZoneRepository::toOwnerID(int32 zoneID)
{
    return zoneID / CONSTS_MAX_SLAVE_ID;
}

bool D1ZoneRepository::isOwnerZone(int32 zoneID, int32 ownerID)
{
    return ownerID == D1ZoneRepository::toOwnerID(zoneID);
}
