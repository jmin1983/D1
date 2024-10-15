//
// D1ZoneDynamicAttributes.cpp
//
// Library: D1EQData
// Package: Zone
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1EQData.h"
#include "D1ZoneDynamicAttributes.h"
#include "D1ZoneAttributePlugin.h"
#include "D1ZoneRepository.h"

#include <D1Base/D1RedisClientInterface.h>
#include <D1Message/D1MessageObject.h>
#include <D1Message/D1MessageSender.h>

#include <D1Base/D1Consts.h>

using namespace BnD;

bool D1ZoneDynamicAttributes::_writeOperatorChangedLog(false);

D1ZoneDynamicAttributes::D1ZoneDynamicAttributes()
    : D1NotifiableObject()
    , D1RedisHashmapObject()
    , _serviceID(D1Consts::SERVICE_ID_INVALID)
    , _zoneID("ZoneID", D1Consts::ID_INVALID)
    , _plugin(NULL)
{
}

D1ZoneDynamicAttributes::D1ZoneDynamicAttributes(int32 zoneID, int32 serviceID)
    : D1NotifiableObject()
    , D1RedisHashmapObject()
    , _serviceID(serviceID)
    , _zoneID("ZoneID", zoneID)
    , _plugin(NULL)
{
}

D1ZoneDynamicAttributes::~D1ZoneDynamicAttributes()
{
}

void D1ZoneDynamicAttributes::archiveTo(B1Archive* archive) const
{
    writeDataToArchive(_zoneID, archive);
}

void D1ZoneDynamicAttributes::unarchiveFrom(const B1Archive& archive)
{
    readDataFromArchive(archive, &_zoneID);
}

B1String D1ZoneDynamicAttributes::redisKey() const
{
    assert(zoneID() != D1Consts::ID_INVALID);
    return zoneID() != D1Consts::ID_INVALID ? B1String::formatAs("ZoneDynamicAttributes:%d", zoneID()) : "";
}

bool D1ZoneDynamicAttributes::isOwnerZone() const
{
    return D1ZoneRepository::isOwnerZone(zoneID(), _serviceID);
}

void D1ZoneDynamicAttributes::reloadStates(D1RedisClientInterface* redisReader)
{
    const B1String key = redisKey();
    if (key.isEmpty()) {
        assert(false);
    }
    else {
        std::map<B1String, B1String> out;
        redisReader->hgetall(key, &out);
        readRedisMap(out);
    }
}

void D1ZoneDynamicAttributes::notifyAttributesChanged(D1RedisClientInterface* delayedCommander, bool isEssential) const
{
    const auto notifyString = toMessage();
    if (_plugin) {
        _plugin->implNotifyAttributesChanged(zoneID(), notifyString, isCostAffectable());
    }
    if (delayedCommander) {
        delayedCommander->publish(D1MessageSender::updateZoneAttributesChannel(D1ZoneRepository::toOwnerID(zoneID())), notifyString, isEssential);
    }
}
