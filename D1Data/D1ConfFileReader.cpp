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

B1String D1ConfFileReader::defaultLogPath() const
{
    return B1SystemUtil::getCurrentDirectory() + "/appLog";
}

int32 D1ConfFileReader::defaultLogDays() const
{
    return 30;  //  30 days.
}

B1String D1ConfFileReader::implToString() const
{
    B1String result;
    result.appendf("\nconfig_logPath(empty to default):[%s], defalut:[%s]", _logPath.cString(), defaultLogPath().cString());
    result.appendf("\nconfig_adminAddress:[%s]", _adminAddress.cString());
    result.appendf("\nconfig_logDays(0 to default):[%d], default[%d]", _logDays, defaultLogDays());
    result.appendf("\nconfig_adminPort:[%d]", _adminPort);
    result.appendf("\nconfig_adminDB:[%d]", _adminDB);
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

bool D1ConfFileReader::saveDefault()
{
    return implSave(configFilePath());
}

B1String D1ConfFileReader::logPath() const
{
    return _logPath.isEmpty() ? defaultLogPath() : _logPath.copy();
}

int32 D1ConfFileReader::logCounts() const
{
    const int32 hoursPerDay = 24;
    return hoursPerDay * (_logDays > 0 ? _logDays : defaultLogDays());
}
