//
// D1RedisHashmapObject.cpp
//
// Library: D1Data
// Package: D1Data
// Module:  D1Data
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Data.h"
#include "D1RedisHashmapObject.h"

#include <B1Base/B1StringUtil.h>

#include <D1Base/D1RedisClientInterface.h>

using namespace BnD;

bool D1RedisHashmapObject::implWriteToRedisNow(D1RedisClientInterface* blockedCommander) const
{
    auto args = prepareRedisStringArgs();
    if (args.empty()) {
        return false;
    }
    makeRedisStringArgs(&args);
    return blockedCommander->blockedCommand(args);
}

bool D1RedisHashmapObject::implWriteToRedis(D1RedisClientInterface* writer) const
{
    auto args = prepareRedisStringArgs();
    if (args.empty()) {
        return false;
    }
    makeRedisStringArgs(&args);
    return writer->nonBlockedCommand(args, true);
}

bool D1RedisHashmapObject::implReadFromRedis(D1RedisClientInterface* reader)
{
    auto key = redisKey();
    if (key.isEmpty()) {
        assert(false);
        return false;
    }
    std::map<B1String, B1String> out;
    if (reader->hgetall(key, &out) != true) {
        return false;
    }
    return readRedisMap(out);
}

void D1RedisHashmapObject::setRedisString(std::vector<B1String>* args, B1String&& field, int8 value) const
{
    args->push_back(std::move(field));
    args->push_back(B1String::formatAs("%d", value));
}

void D1RedisHashmapObject::setRedisString(std::vector<B1String>* args, B1String&& field, int16 value) const
{
    args->push_back(std::move(field));
    args->push_back(B1String::formatAs("%d", value));
}

void D1RedisHashmapObject::setRedisString(std::vector<B1String>* args, B1String&& field, int32 value) const
{
    args->push_back(std::move(field));
    args->push_back(B1String::formatAs("%d", value));
}

void D1RedisHashmapObject::setRedisString(std::vector<B1String>* args, B1String&& field, int64 value) const
{
    args->push_back(std::move(field));
    args->push_back(B1String::formatAs("%lld", value));
}

void D1RedisHashmapObject::setRedisString(std::vector<B1String>* args, B1String&& field, uint8 value) const
{
    args->push_back(std::move(field));
    args->push_back(B1String::formatAs("%u", value));
}

void D1RedisHashmapObject::setRedisString(std::vector<B1String>* args, B1String&& field, uint16 value) const
{
    args->push_back(std::move(field));
    args->push_back(B1String::formatAs("%u", value));
}

void D1RedisHashmapObject::setRedisString(std::vector<B1String>* args, B1String&& field, uint32 value) const
{
    args->push_back(std::move(field));
    args->push_back(B1String::formatAs("%u", value));
}

void D1RedisHashmapObject::setRedisString(std::vector<B1String>* args, B1String&& field, uint64 value) const
{
    args->push_back(std::move(field));
    args->push_back(B1String::formatAs("%llu", value));
}

void D1RedisHashmapObject::setRedisString(std::vector<B1String>* args, B1String&& field, float32 value) const
{
    args->push_back(std::move(field));
    args->push_back(B1String::formatAs("%f", value));
}

void D1RedisHashmapObject::setRedisString(std::vector<B1String>* args, B1String&& field, float64 value) const
{
    args->push_back(std::move(field));
    args->push_back(B1String::formatAs("%lf", value));
}

void D1RedisHashmapObject::setRedisString(std::vector<B1String>* args, B1String&& field, const B1String& value) const
{
    if (value.isEmpty() != true) {
        args->push_back(std::move(field));
        args->push_back(value.copy());
    }
}

void D1RedisHashmapObject::setRedisString(std::vector<B1String>* args, B1String&& field, B1String&& value) const
{
    if (value.isEmpty() != true) {
        args->push_back(std::move(field));
        args->push_back(std::move(value));
    }
}

void D1RedisHashmapObject::setRedisString(std::vector<B1String>* args, B1String&& field, const std::vector<int32>& value) const
{
    B1String valueString;
    if (B1StringUtil::vectorIntToString(value, &valueString)) {
        setRedisString(args, std::move(field), valueString);
    }
}

bool D1RedisHashmapObject::readFromRedisMap(const std::map<B1String, B1String>& map, const B1String& field, int8* data, int8 defaultValue) const
{
    auto itr = map.find(field);
    if (itr != map.end() && itr->second.isEmpty() != true) {
        try {
            *data = itr->second.toInt8();
            return true;
        }
        catch (...) {
            *data = defaultValue;
        }
    }
    else {
        *data = defaultValue;
    }
    return false;
}

bool D1RedisHashmapObject::readFromRedisMap(const std::map<B1String, B1String>& map, const B1String& field, int16* data, int16 defaultValue) const
{
    auto itr = map.find(field);
    if (itr != map.end() && itr->second.isEmpty() != true) {
        try {
            *data = itr->second.toInt16();
            return true;
        }
        catch (...) {
            *data = defaultValue;
        }
    }
    else {
        *data = defaultValue;
    }
    return false;
}

bool D1RedisHashmapObject::readFromRedisMap(const std::map<B1String, B1String>& map, const B1String& field, int32* data, int32 defaultValue) const
{
    auto itr = map.find(field);
    if (itr != map.end() && itr->second.isEmpty() != true) {
        try {
            *data = itr->second.toInt32();
            return true;
        }
        catch (...) {
            *data = defaultValue;
        }
    }
    else {
        *data = defaultValue;
    }
    return false;
}

bool D1RedisHashmapObject::readFromRedisMap(const std::map<B1String, B1String>& map, const B1String& field, int64* data, int64 defaultValue) const
{
    auto itr = map.find(field);
    if (itr != map.end() && itr->second.isEmpty() != true) {
        try {
            *data = itr->second.toInt64();
            return true;
        }
        catch (...) {
            *data = defaultValue;
        }
    }
    else {
        *data = defaultValue;
    }
    return false;
}

bool D1RedisHashmapObject::readFromRedisMap(const std::map<B1String, B1String>& map, const B1String& field, uint8* data, uint8 defaultValue) const
{
    auto itr = map.find(field);
    if (itr != map.end() && itr->second.isEmpty() != true) {
        try {
            *data = itr->second.toUint8();
            return true;
        }
        catch (...) {
            *data = defaultValue;
        }
    }
    else {
        *data = defaultValue;
    }
    return false;
}

bool D1RedisHashmapObject::readFromRedisMap(const std::map<B1String, B1String>& map, const B1String& field, uint16* data, uint16 defaultValue) const
{
    auto itr = map.find(field);
    if (itr != map.end() && itr->second.isEmpty() != true) {
        try {
            *data = itr->second.toUint16();
            return true;
        }
        catch (...) {
            *data = defaultValue;
        }
    }
    else {
        *data = defaultValue;
    }
    return false;
}

bool D1RedisHashmapObject::readFromRedisMap(const std::map<B1String, B1String>& map, const B1String& field, uint32* data, uint32 defaultValue) const
{
    auto itr = map.find(field);
    if (itr != map.end() && itr->second.isEmpty() != true) {
        try {
            *data = itr->second.toUint32();
            return true;
        }
        catch (...) {
            *data = defaultValue;
        }
    }
    else {
        *data = defaultValue;
    }
    return false;
}

bool D1RedisHashmapObject::readFromRedisMap(const std::map<B1String, B1String>& map, const B1String& field, uint64* data, uint64 defaultValue) const
{
    auto itr = map.find(field);
    if (itr != map.end() && itr->second.isEmpty() != true) {
        try {
            *data = itr->second.toUint64();
            return true;
        }
        catch (...) {
            *data = defaultValue;
        }
    }
    else {
        *data = defaultValue;
    }
    return false;
}

bool D1RedisHashmapObject::readFromRedisMap(const std::map<B1String, B1String>& map, const B1String& field, float32* data, float32 defaultValue) const
{
    auto itr = map.find(field);
    if (itr != map.end() && itr->second.isEmpty() != true) {
        try {
            *data = itr->second.toFloat32();
            return true;
        }
        catch (...) {
            *data = defaultValue;
        }
    }
    else {
        *data = defaultValue;
    }
    return false;
}

bool D1RedisHashmapObject::readFromRedisMap(const std::map<B1String, B1String>& map, const B1String& field, float64* data, float64 defaultValue) const
{
    auto itr = map.find(field);
    if (itr != map.end() && itr->second.isEmpty() != true) {
        try {
            *data = itr->second.toFloat64();
            return true;
        }
        catch (...) {
            *data = defaultValue;
        }
    }
    else {
        *data = defaultValue;
    }
    return false;
}

bool D1RedisHashmapObject::readFromRedisMap(const std::map<B1String, B1String>& map, const B1String& field, B1String* data, B1String&& defaultValue) const
{
    auto itr = map.find(field);
    if (itr != map.end()) {
        *data = itr->second.copy();
        return true;
    }
    else {
        *data = std::move(defaultValue);
    }
    return false;
}

bool D1RedisHashmapObject::readFromRedisMap(const std::map<B1String, B1String>& map, const B1String& field, std::vector<int32>* data) const
{
    auto itr = map.find(field);
    if (itr != map.end()) {
        const B1String& valueString = itr->second;
        if (valueString.isEmpty() != true) {
            return B1StringUtil::stringToVectorInt(valueString, data);
        }
    }
    return false;
}

auto D1RedisHashmapObject::prepareRedisStringArgs() const -> std::vector<B1String>
{
    auto key = redisKey();
    if (key.isEmpty()) {
        assert(false);
        return std::vector<B1String>();
    }
    if (isValidToMakeRedisString() != true) {
        return std::vector<B1String>();
    }
    std::vector<B1String> args;
    args.reserve(20);
    args.push_back("HMSET");
    args.push_back(std::move(key));
    return args;
}

bool D1RedisHashmapObject::writeToRedisNow(D1RedisClientInterface* blockedCommander) const
{
    return implWriteToRedisNow(blockedCommander);
}

bool D1RedisHashmapObject::writeToRedis(D1RedisClientInterface* writer) const
{
    return implWriteToRedis(writer);
}

bool D1RedisHashmapObject::readFromRedis(D1RedisClientInterface* reader)
{
    return implReadFromRedis(reader);
}
