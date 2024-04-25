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

#include <B1Base/B1SystemUtil.h>

#include <boost/property_tree/json_parser.hpp>

using namespace BnD;

D1ConfFileReader::D1ConfFileReader()
    : D1RawFileReader()
    , _logPath("")
    , _adminAddress("127.0.0.1")
    , _logDays(0)
    , _adminPort(6379)
    , _adminDB(0)
{
}

D1ConfFileReader::~D1ConfFileReader()
{
}

B1String D1ConfFileReader::implConfigFilePath() const
{
    return B1SystemUtil::getCurrentDirectory() + "/config/config.json";
}

B1String D1ConfFileReader::defaultLogPath(const B1String& serviceNameInLowerCase) const
{
    return B1String::formatAs("%s/appLog/%s", B1SystemUtil::getCurrentDirectory().cString(), serviceNameInLowerCase.cString());
}

int32 D1ConfFileReader::defaultLogDays() const
{
    return 30;  //  30 days.
}

B1String D1ConfFileReader::implToString() const
{
    B1String result;
    result.appendf("config_logPath(empty to default):[%s]\n", _logPath.cString());
    result.appendf("config_adminAddress:[%s]\n", _adminAddress.cString());
    result.appendf("config_logDays(0 to default):[%d]\n", _logDays);
    result.appendf("config_adminPort:[%d]\n", _adminPort);
    result.appendf("config_adminDB:[%d]\n", _adminDB);
    return result;
}

bool D1ConfFileReader::validate() const
{
    return _adminAddress.isEmpty() != true && _adminPort > 0;
}

bool D1ConfFileReader::readData()
{
    getString("LogPath", &_logPath);
    getInt32("LogDays", &_logDays);
    if (getString("AdminAddress", &_adminAddress) != true) {
        return false;
    }
    if (getInt32("AdminPort", &_adminPort) != true) {
        return false;
    }
    if (getInt32("AdminDB", &_adminDB) != true) {
        return false;
    }
    return true;
}

bool D1ConfFileReader::writeData()
{
    putString("LogPath", _logPath);
    putInt32("LogDays", _logDays);
    if (putString("AdminAddress", _adminAddress) != true) {
        return false;
    }
    if (putInt32("AdminPort", _adminPort) != true) {
        return false;
    }
    if (putInt32("AdminDB", _adminDB) != true) {
        return false;
    }
    return true;
}

B1String D1ConfFileReader::configFilePath() const
{
    return implConfigFilePath();
}

bool D1ConfFileReader::loadDefault()
{
    return implLoad(configFilePath());
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
