//
// D1ConfFileReader.cpp
//
// Library: D1Data
// Package: D1Data
// Module:  D1Data
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Data.h"
#include "D1ConfFileReader.h"

#include <B1Base/B1StringUtil.h>
#include <B1Base/B1SystemUtil.h>

#include <boost/property_tree/json_parser.hpp>

using namespace BnD;

D1ConfFileReader::D1ConfFileReader()
    : _pt()
    , _logPath("")
    , _redisAddress("127.0.0.1")
    , _logDays(0)
    , _redisPort(6379)
    , _redisDB(0)
{
}

D1ConfFileReader::~D1ConfFileReader()
{
}

B1String D1ConfFileReader::implToString() const
{
    B1String result;
    result.appendf("config_logPath(empty to default):[%s]\n", _logPath.cString());
    result.appendf("config_redisAddress:[%s]\n", _redisAddress.cString());
    result.appendf("config_logDays(0 to default):[%d]\n", _logDays);
    result.appendf("config_redisPort:[%d]\n", _redisPort);
    result.appendf("config_redisDB:[%d]\n", _redisDB);
    return result;
}

B1String D1ConfFileReader::implConfigFilePath() const
{
    return B1SystemUtil::getCurrentDirectory() + "/config/config.json";
}

bool D1ConfFileReader::implLoad(const B1String& filePath)
{
    if (B1SystemUtil::isFileExist(filePath) != true) {
        return false;
    }
    try {
        boost::property_tree::read_json(filePath.cString(), _pt);
    }
    catch (...) {
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

bool D1ConfFileReader::implSave(const B1String& filePath)
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
    try {
        boost::property_tree::write_json(filePath.to_string(), _pt);
    }
    catch (...) {
        return false;
    }
    return true;
}

bool D1ConfFileReader::validate() const
{
    return _redisAddress.isEmpty() != true && _redisPort > 0;
}

bool D1ConfFileReader::readData()
{
    try { _logPath = _pt.get<std::string>("LogPath"); } catch (...) {}
    try { _logDays = _pt.get<int32>("LogDays"); } catch (...) {}
    try {
        _redisAddress = _pt.get<std::string>("AdminAddress");
        _redisPort = _pt.get<int32>("AdminPort");
        _redisDB = _pt.get<int32>("AdminDB");
    }
    catch (...) {
        return false;
    }
    return true;
}

bool D1ConfFileReader::writeData()
{
    try { _pt.put("LogPath", _logPath.to_string()); } catch (...) {}
    try { _pt.put("LogDays", _logDays); } catch (...) {}
    try {
        _pt.put("AdminAddress", _redisAddress.to_string());
        _pt.put("AdminPort", _redisPort);
        _pt.put("AdminDB", _redisDB);
    }
    catch (...) {
        return false;
    }
    return true;
}

B1String D1ConfFileReader::defaultLogPath(const B1String& serviceNameInLowerCase) const
{
    return B1String::formatAs("%s/appLog/%s", B1SystemUtil::getCurrentDirectory().cString(), serviceNameInLowerCase.cString());
}

int32 D1ConfFileReader::defaultLogDays() const
{
    return 30;  //  30 days.
}

B1String D1ConfFileReader::toString() const
{
    return implToString();
}

B1String D1ConfFileReader::configFilePath() const
{
    return implConfigFilePath();
}

bool D1ConfFileReader::load()
{
    return implLoad(configFilePath());
}

bool D1ConfFileReader::load(const B1String& filePath)
{
    return implLoad(filePath);
}

bool D1ConfFileReader::save(const B1String& filePath)
{
    return implSave(filePath);
}

B1String D1ConfFileReader::logPath(const B1String& serviceName) const
{
    B1String lower(serviceName.copy());
    lower.makeLower();
    if (_logPath.isEmpty()) {
        return defaultLogPath(lower);
    }
    else {
        return B1String::formatAs("%s/%s", _logPath.cString(), lower.cString());
    }
}

int32 D1ConfFileReader::logCounts() const
{
    const int32 hoursPerDay = 24;
    return hoursPerDay * (_logDays > 0 ? _logDays : defaultLogDays());
}
