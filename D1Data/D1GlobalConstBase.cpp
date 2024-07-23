//
// D1GlobalConstBase.cpp
//
// Library: D1Data
// Package: D1Data
// Module:  D1Data
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Data.h"
#include "D1GlobalConstBase.h"

#include <D1Base/D1RedisClientInterface.h>

using namespace BnD;

B1String D1GlobalConstBase::ItemBunch::itemField(const B1String& field) const
{
    return _itemBunchName.isEmpty() ? field.copy() : _itemBunchName + "_" + field;
}

B1String D1GlobalConstBase::ItemBunch::itemFieldAndValue(const DataInt32& itemData) const
{
    return B1String::formatAs("%s[%d]", itemField(itemData.first).cString(), itemData.second);
}

B1String D1GlobalConstBase::ItemBunch::itemFieldAndValue(const DataFloat64& itemData) const
{
    return B1String::formatAs("%s[%f]", itemField(itemData.first).cString(), itemData.second);
}

B1String D1GlobalConstBase::ItemBunch::itemFieldAndValue(const DataString& itemData) const
{
    return B1String::formatAs("%s[%s]", itemField(itemData.first).cString(), itemData.second.cString());
}

B1String D1GlobalConstBase::itemKey() const
{
    return "System:Configuration:" + _processName;
}

void D1GlobalConstBase::loadData(bool isDynamic, D1RedisClientInterface* redisClientInterface, const B1String& key, bool adjustValue)
{
    if (_itemBunches.empty()) {
        return;
    }
    std::map<B1String, B1String> values;
    if (redisClientInterface->hgetall(key, &values) != true) {
        return;
    }
    for (const auto& itemBunchesPair : _itemBunches) {
        itemBunchesPair.second->loadData(isDynamic, this, values, adjustValue);
    }
}

bool D1GlobalConstBase::addItemBunch(std::shared_ptr<ItemBunch> itemBunch)
{
    auto itr = _itemBunches.find(itemBunch->itemBunchName());
    if (itr != _itemBunches.end()) {
        assert(false);
        return false;
    }
    _itemBunches.insert(std::make_pair(itemBunch->itemBunchName().copy(), itemBunch));
    return true;
}

bool D1GlobalConstBase::addAllItems()
{
    return implAddAllItems();
}

void D1GlobalConstBase::loadAllData(D1RedisClientInterface* redisClientInterface)
{
    if (_id != D1Consts::ID_INVALID) {
        loadData(false, redisClientInterface, itemKey());
        loadData(false, redisClientInterface, B1String::formatAs("%s:%d", itemKey().cString(), _id), true);
    }
    else {
        loadData(false, redisClientInterface, itemKey(), true);
    }
    reloadDynamicData(redisClientInterface);
}

void D1GlobalConstBase::reloadDynamicData(D1RedisClientInterface* redisClientInterface)
{
    if (_id != D1Consts::ID_INVALID) {
        loadData(true, redisClientInterface, itemKey());
        loadData(true, redisClientInterface, B1String::formatAs("%s:%d", itemKey().cString(), _id), true);
    }
    else {
        loadData(true, redisClientInterface, itemKey(), true);
    }
}

void D1GlobalConstBase::saveAllData(D1RedisClientInterface* redisClientInterface)
{
    for (const auto& itemBunchesPair : _itemBunches) {
        std::vector<B1String> args;
        args.reserve(20);
        args.push_back("HMSET");
        args.push_back(itemKey());
        if (itemBunchesPair.second->makeRedisStringArgs(&args)) {
            redisClientInterface->blockedCommand(args);
        }
    }
}

B1String D1GlobalConstBase::toString() const
{
    B1String s;
    for (const auto& itemBunchesPair : _itemBunches) {
        s.appendf("\n%s", itemBunchesPair.second->toString().cString());
    }
    return s;
}

bool D1GlobalConstBase::getStringData(const std::map<B1String, B1String>& values, const B1String& key, B1String* data)
{
    auto itr = values.find(key);
    if (itr == values.end()) {
        return false;
    }
    try {
        *data = itr->second.copy();
    }
    catch (...) {
        return false;
    }
    return true;
}