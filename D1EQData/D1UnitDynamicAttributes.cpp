//
// D1UnitDynamicAttributes.cpp
//
// Library: D1EQData
// Package: Unit
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1EQData.h"
#include "D1UnitDynamicAttributes.h"

#include <D1Base/D1RedisClientInterface.h>
//#include <D1Message/D1MessageObject.h>
#include <D1Message/D1MessageSender.h>

#include <D1Base/D1Consts.h>

using namespace BnD;

D1UnitDynamicAttributes::D1UnitDynamicAttributes()
    : D1NotifiableObject()
    , D1RedisHashmapObject()
    , _unitID("UnitID", D1Consts::ID_INVALID)
{
}

D1UnitDynamicAttributes::D1UnitDynamicAttributes(int32 unitID)
    : D1NotifiableObject()
    , D1RedisHashmapObject()
    , _unitID("UnitID", unitID)
{
}

D1UnitDynamicAttributes::~D1UnitDynamicAttributes()
{
}

void D1UnitDynamicAttributes::archiveTo(B1Archive* archive) const
{
    writeDataToArchive(_unitID, archive);
}

void D1UnitDynamicAttributes::unarchiveFrom(const B1Archive& archive)
{
    readDataFromArchive(archive, &_unitID);
}

B1String D1UnitDynamicAttributes::redisKey() const
{
    assert(unitID() != D1Consts::ID_INVALID);
    return unitID() != D1Consts::ID_INVALID ? B1String::formatAs("UnitDynamicAttributes:%d", unitID()) : "";
}

void D1UnitDynamicAttributes::reloadStates(D1RedisClientInterface* redisReader)
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

void D1UnitDynamicAttributes::notifyAttributesChanged(D1RedisClientInterface* delayedCommander, bool isEssential) const
{
    if (delayedCommander) {
        delayedCommander->publish(D1MessageSender::updateUnitAttributesChannel(), toMessage(), isEssential);
    }
}
