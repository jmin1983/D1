//
// D1RawFileReader.cpp
//
// Library: D1Data
// Package: D1Data
// Module:  D1Data
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Data.h"
#include "D1RawFileReader.h"
#include "D1JSONReadWriter.h"

#include <B1Base/B1StringUtil.h>
#include <B1Base/B1SystemUtil.h>

using namespace BnD;

D1RawFileReader::D1RawFileReader()
    : _jsonReadWriter(new D1JSONReadWriter())
{
}

D1RawFileReader::~D1RawFileReader()
{
}

bool D1RawFileReader::implLoad(const B1String& filePath)
{
    if (B1SystemUtil::isFileExist(filePath) != true) {
        return false;
    }
    if (readJSON(filePath) != true) {
        return false;
    }
    if (readData() != true) {
        return false;
    }
    if (validate() != true) {
        return false;
    }
    return true;
}

bool D1RawFileReader::implSave(const B1String& filePath)
{
    if (validate() != true) {
        return false;
    }
    if (writeData() != true) {
        return false;
    }
    B1String directoryPath = filePath.copy();
    B1StringUtil::removeLastPathComponent(&directoryPath);
    B1SystemUtil::createDirectory(directoryPath);
    return writeJSON(filePath);
}

bool D1RawFileReader::readJSON(const B1String& filePath)
{
    return _jsonReadWriter->readJSON(filePath);
}

bool D1RawFileReader::writeJSON(const B1String& filePath)
{
    return _jsonReadWriter->writeJSON(filePath);
}

bool D1RawFileReader::getBool(const B1String& path, bool* value) const
{
    return _jsonReadWriter->get(path, value);
}

bool D1RawFileReader::getInt32(const B1String& path, int32* value) const
{
    return _jsonReadWriter->get(path, value);
}

bool D1RawFileReader::getString(const B1String& path, B1String* value) const
{
    std::string string;
    if (_jsonReadWriter->get(path, &string) != true) {
        return false;
    }
    value->from(std::move(string));
    return true;
}

bool D1RawFileReader::putBool(const B1String& path, bool value)
{
    return _jsonReadWriter->put(path, value);
}

bool D1RawFileReader::putInt32(const B1String& path, int32 value)
{
    return _jsonReadWriter->put(path, value);
}

bool D1RawFileReader::putString(const B1String& path, const B1String& value)
{
    return _jsonReadWriter->put(path, value.to_string());
}

B1String D1RawFileReader::toString() const
{
    return implToString();
}

bool D1RawFileReader::load(const B1String& filePath)
{
    return implLoad(filePath);
}

bool D1RawFileReader::save(const B1String& filePath)
{
    return implSave(filePath);
}
