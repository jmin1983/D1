//
// D1RedisClientInterface.h
//
// Library: D1Base
// Package: D1Base
// Module:  D1Base
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1BASE_REDIS_CLIENT_INTERFACE_H
#define _D1BASE_REDIS_CLIENT_INTERFACE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <list>
#include <map>
#include <set>

namespace BnD {
    class B1RedisDirectClient;
    class D1RedisClientInterface {
    public:
        D1RedisClientInterface(B1RedisDirectClient* directClient);
        virtual ~D1RedisClientInterface();
    protected:
        B1RedisDirectClient* _redisDirectClient;
    public:
        bool startPolling();
        void stopPolling();
        void startWriting();
    public:
        bool getAllStrings(const std::vector<B1String>& args, std::list<B1String>* out);
        bool exists(const B1String& key);
        bool subscribe(std::set<B1String>&& channels);
        bool hmget(const B1String& key, const std::vector<B1String>& fields, std::vector<B1String>* out);
        B1String hmget(const B1String& key, const B1String& field);
        bool hgetall(const B1String& key, std::map<B1String, B1String>* out);
        bool scan(const B1String& pattern, std::set<B1String>* out, int32 count = -1);
        bool smembers(const B1String& key, std::list<B1String>* out);
        bool incr(const B1String& key, int64* result);
        bool time(uint64* seconds, uint32* microseconds, bool ignoreAdjustSecond = false);
        bool blockedCommand(const std::vector<B1String>& args, B1String* out = NULL);
        void blockedCommand(const std::vector<std::vector<B1String> >& cmds);
        bool nonBlockedCommand(const std::vector<B1String>& args, bool isEssential);
        bool hmset(const B1String& key, const B1String& field, const B1String& value, bool isEssential);
        bool hmset(const B1String& key, const std::map<B1String, B1String>& fieldValues, bool isEssential);
        bool hdel(const B1String& key, const B1String& field);  //  using _commandEssentials.
        bool del(const B1String& key);                          //  using _commandEssentials.
        bool sadd(const B1String& key, const B1String& value);  //  using _commandEssentials.
        bool srem(const B1String& key, const B1String& value);  //  using _commandEssentials.
        bool rpush(const B1String& key, const B1String& value); //  using _commands.
        bool publish(const B1String& channel, const B1String& message, bool isEssential);
    };
}   //  !BnD

#endif  // !_D1BASE_REDIS_CLIENT_INTERFACE_H
