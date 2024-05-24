//
// D1RedisHashmapObject.h
//
// Library: D1Data
// Package: D1Data
// Module:  D1Data
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1DATA_REDIS_HASHMAP_OBJECT_H
#define _D1DATA_REDIS_HASHMAP_OBJECT_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <B1Base/B1DataType.h>

#include <map>

namespace BnD {
    class D1RedisClientInterface;
    class D1RedisHashmapObject {
    public:
        D1RedisHashmapObject() {}
        virtual ~D1RedisHashmapObject() {}
    protected:
        virtual B1String redisKey() const = 0;
        virtual bool isValidToMakeRedisString() const = 0;
        virtual void makeRedisStringArgs(std::vector<B1String>* args) const = 0;
        virtual bool readRedisMap(const std::map<B1String, B1String>& map) = 0;
        virtual bool implWriteToRedisNow(D1RedisClientInterface* blockedCommander) const;
        virtual bool implWriteToRedis(D1RedisClientInterface* writer) const;
        virtual bool implReadFromRedis(D1RedisClientInterface* reader);
    protected:
        void setRedisString(std::vector<B1String>* args, B1String&& field, int32 value) const;
        void setRedisString(std::vector<B1String>* args, B1String&& field, int64 value) const;
        void setRedisString(std::vector<B1String>* args, B1String&& field, uint32 value) const;
        void setRedisString(std::vector<B1String>* args, B1String&& field, uint64 value) const;
        void setRedisString(std::vector<B1String>* args, B1String&& field, float64 value) const;
        void setRedisString(std::vector<B1String>* args, B1String&& field, const B1String& value) const;
        void setRedisString(std::vector<B1String>* args, B1String&& field, B1String&& value) const;
        template <typename T>
        void setRedisString(std::vector<B1String>* args, const T& data) const
        {
            setRedisString(args, data.first.copy(), data.second);
        }
        bool readFromRedisMap(const std::map<B1String, B1String>& map, const B1String& field, int32* data, int32 defaultValue = -1) const;
        bool readFromRedisMap(const std::map<B1String, B1String>& map, const B1String& field, int64* data, int32 defaultValue = -1) const;
        bool readFromRedisMap(const std::map<B1String, B1String>& map, const B1String& field, uint32* data, uint32 defaultValue = 0) const;
        bool readFromRedisMap(const std::map<B1String, B1String>& map, const B1String& field, uint64* data, uint32 defaultValue = 0) const;
        bool readFromRedisMap(const std::map<B1String, B1String>& map, const B1String& field, float64* data, uint32 defaultValue = -1) const;
        bool readFromRedisMap(const std::map<B1String, B1String>& map, const B1String& field, B1String* data, B1String&& defaultValue = "") const;
        template <typename T>
        bool readFromRedisMap(const std::map<B1String, B1String>& map, T* data) const
        {
            return readFromRedisMap(map, data->first, &data->second);
        }
        template <typename T>
        bool readFromRedisMapCastInt32(const std::map<B1String, B1String>& map, const B1String& field, T* value, T defaultValue)
        {
            int32 temp = 0;
            bool result = readFromRedisMap(map, field, &temp);
            if (temp < 0) {
                *value = defaultValue;
                result = false;
            }
            else {
                *value = static_cast<T>(temp);
            }
            return result;
        }
        std::vector<B1String> prepareRedisStringArgs() const;
    public:
        bool writeToRedisNow(D1RedisClientInterface* blockedCommander) const;
        bool writeToRedis(D1RedisClientInterface* writer) const;
        bool readFromRedis(D1RedisClientInterface* reader);
    };
}   //  !BnD

#endif  // !_D1DATA_REDIS_HASHMAP_OBJECT_H
