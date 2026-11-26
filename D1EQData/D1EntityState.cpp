//
// D1EntityState.cpp
//
// Library: D1EQData
// Package: D1EQData
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1EQData.h"
#include "D1EntityState.h"

#include <D1Base/D1RedisClientInterface.h>
//#include <D1Message/D1MessageObject.h>
#include <D1Message/D1MessageSender.h>

using namespace BnD;

D1EntityState::D1EntityState()
    : D1NotifiableObject()
    , D1RedisHashmapObject()
    , _name("Name", "")
{
}

D1EntityState::D1EntityState(B1String&& name)
    : D1NotifiableObject()
    , D1RedisHashmapObject()
    , _name("Name", std::move(name))
{
}

D1EntityState::~D1EntityState()
{
}

void D1EntityState::archiveTo(B1Archive* archive) const
{
    writeDataToArchive(_name, archive);
}

void D1EntityState::unarchiveFrom(const B1Archive& archive)
{
    readDataFromArchive(archive, &_name);
}

B1String D1EntityState::redisKey() const
{
    return "EntityState";
}

void D1EntityState::makeRedisStringArgs(std::vector<B1String>* args) const
{
    setRedisString(args, _name);
}

bool D1EntityState::readRedisMap(const std::map<B1String, B1String>& map)
{
    readFromRedisMap(map, &_name);
    return true;
}

void D1EntityState::reloadStates(D1RedisClientInterface* redisReader)
{
    const B1String key = redisKey();
    std::map<B1String, B1String> out;
    redisReader->hgetall(key, &out);
    readRedisMap(out);
}

void D1EntityState::notifyAttributesChanged(D1RedisClientInterface* delayedCommander, bool isEssential) const
{
    assert(delayedCommander != nullptr);
    const auto notifyString = toMessage();
    if (delayedCommander) {
        delayedCommander->publish(D1MessageSender::updateEntityStateChannel(), notifyString, isEssential);
    }
}
