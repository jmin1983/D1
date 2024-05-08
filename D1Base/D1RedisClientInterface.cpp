//
// D1RedisClientInterface.cpp
//
// Library: D1Base
// Package: D1Base
// Module:  D1Base
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Base.h"
#include "D1RedisClientInterface.h"

#include <B1Redic/B1RedisDirectClient.h>

using namespace BnD;

D1RedisClientInterface::D1RedisClientInterface(B1RedisDirectClient* directClient)
    : _redisDirectClient(directClient)
{
}

D1RedisClientInterface::~D1RedisClientInterface()
{
}

bool D1RedisClientInterface::getAllStrings(const std::vector<B1String>& args, std::list<B1String>* out)
{
    if (_redisDirectClient) {
        return _redisDirectClient->blockedCommand(args, out);
    }
    return false;
}

bool D1RedisClientInterface::startPolling()
{
    if (_redisDirectClient) {
        return _redisDirectClient->startPolling();
    }
    return false;
}

void D1RedisClientInterface::startWriting()
{
    if (_redisDirectClient) {
        _redisDirectClient->startWriting();
    }
}


bool D1RedisClientInterface::exists(const B1String& key)
{
    if (_redisDirectClient) {
        return _redisDirectClient->exists(key);
    }
    return false;
}

bool D1RedisClientInterface::subscribe(std::set<B1String>&& channels)
{
    if (_redisDirectClient) {
        return _redisDirectClient->subscribe(std::move(channels));
    }
    return false;
}

bool D1RedisClientInterface::hmget(const B1String& key, const std::vector<B1String>& fields, std::vector<B1String>* out)
{
    if (_redisDirectClient) {
        return _redisDirectClient->hmget(key, fields, out);
    }
    return false;
}

B1String D1RedisClientInterface::hmget(const B1String& key, const B1String& field)
{
    if (_redisDirectClient) {
        return _redisDirectClient->hmget(key, field);
    }
    return "";
}

bool D1RedisClientInterface::hgetall(const B1String& key, std::map<B1String, B1String>* out)
{
    if (_redisDirectClient) {
        return _redisDirectClient->hgetall(key, out);
    }
    return false;
}

bool D1RedisClientInterface::smembers(const B1String& key, std::list<B1String>* out)
{
    if (_redisDirectClient) {
        return _redisDirectClient->smembers(key, out);
    }
    return false;
}

bool D1RedisClientInterface::incr(const B1String& key, int64* result)
{
    if (_redisDirectClient) {
        return _redisDirectClient->incr(key, result);
    }
    return false;
}

bool D1RedisClientInterface::time(uint64* seconds, uint32* microseconds, bool ignoreAdjustSecond)
{
    if (_redisDirectClient) {
        return _redisDirectClient->time(seconds, microseconds, ignoreAdjustSecond);
    }
    return false;
}

void D1RedisClientInterface::time(B1String* result, bool useTimeLength17)
{
    if (_redisDirectClient) {
        _redisDirectClient->time(result, useTimeLength17);
    }
}

void D1RedisClientInterface::timeMMDDHHmmSSnnnn(B1String* result)
{
    if (_redisDirectClient) {
        _redisDirectClient->timeMMDDHHmmSSnnnn(result);
    }
}

bool D1RedisClientInterface::blockedCommand(const std::vector<B1String>& args, B1String* out)
{
    if (_redisDirectClient) {
        if (NULL == out) {
            return _redisDirectClient->blockedCommand(args);
        }
        else {
            std::list<B1String> o;
            if (_redisDirectClient->blockedCommand(args, &o) != true) {
                return false;
            }
            if (o.empty()) {
                return false;
            }
            *out = std::move(o.front());
            return true;
        }
    }
    return false;
}

void D1RedisClientInterface::blockedCommand(const std::vector<std::vector<B1String> >& cmds)
{
    if (_redisDirectClient) {
        _redisDirectClient->blockedCommand(cmds);
    }
}

bool D1RedisClientInterface::nonBlockedCommand(const std::vector<B1String>& args, bool isEssential)
{
    if (_redisDirectClient) {
        return _redisDirectClient->nonBlockedCommand(args, isEssential);
    }
    return false;
}

bool D1RedisClientInterface::hmset(const B1String& key, const B1String& field, const B1String& value, bool isEssential)
{
    if (_redisDirectClient) {



        return _redisDirectClient->hmset(key.copy(), field.copy(), value.copy(), isEssential);




    }
    return false;
}

bool D1RedisClientInterface::hmset(const B1String& key, const std::map<B1String, B1String>& fieldValues, bool isEssential)
{
    if (_redisDirectClient) {
        return _redisDirectClient->hmset(key, fieldValues, isEssential);
    }
    return false;
}

bool D1RedisClientInterface::hdel(const B1String& key, const B1String& field)
{
    if (_redisDirectClient) {
        return _redisDirectClient->hdel(key, field);
    }
    return false;
}

bool D1RedisClientInterface::del(const B1String& key)
{
    if (_redisDirectClient) {
        return _redisDirectClient->del(key);
    }
    return false;
}

bool D1RedisClientInterface::sadd(const B1String& key, const B1String& value)
{
    if (_redisDirectClient) {
        return _redisDirectClient->sadd(key, value);
    }
    return false;
}

bool D1RedisClientInterface::srem(const B1String& key, const B1String& value)
{
    if (_redisDirectClient) {
        return _redisDirectClient->srem(key, value);
    }
    return false;
}

bool D1RedisClientInterface::rpush(const B1String& key, const B1String& value)
{
    if (_redisDirectClient) {
        return _redisDirectClient->rpush(key, value);
    }
    return false;
}

bool D1RedisClientInterface::publish(const B1String& channel, const B1String& message, bool isEssential)
{
    if (_redisDirectClient) {
        return _redisDirectClient->publish(channel, message, isEssential);
    }
    return false;
}

bool D1RedisClientInterface::isDCSAlive(int32 dcsID)
{
    B1String key;
    key.format("DCSInfo:%d:Alive", dcsID);




    const B1String aliveString = hmget(key.copy(), "Alive");





    if (aliveString.isEmpty() != true) {
        try {
            return aliveString.toInt32() == 1;
        }
        catch (...) {}
    }
    return false;
}