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
    , _logPath("LogPath", "")
    , _adminAddress("AdminAddress", "127.0.0.1")
    , _logDays("LogDays", 0)
    , _adminPort("AdminPort", 6379)
    , _adminDB("AdminDB", 0)
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
    return 30 * 6;  //  6 month.
}

B1String D1ConfFileReader::implToString() const
{
    B1String result;
    result.appendf("\nconfig_logPath(empty to default):[%s], defalut:[%s]", logPath().cString(), defaultLogPath().cString());
    result.appendf("\nconfig_adminAddress:[%s]", adminAddress().cString());
    result.appendf("\nconfig_logDays(0 to default):[%d], default[%d]", logDays(), defaultLogDays());
    result.appendf("\nconfig_adminPort:[%d]", adminPort());
    result.appendf("\nconfig_adminDB:[%d]", adminDB());
    return result;
}

bool D1ConfFileReader::validate() const
{
    return adminAddress().isEmpty() != true && adminPort() > 0;
}

bool D1ConfFileReader::readData()
{
    getData(&_logPath);
    getData(&_logDays);
    if (getData(&_adminAddress) != true) {
        return false;
    }
    if (getData(&_adminPort) != true) {
        return false;
    }
    if (getData(&_adminDB) != true) {
        return false;
    }
    return true;
}

bool D1ConfFileReader::writeData()
{
    putData(_logPath);
    putData(_logDays);
    if (putData(_adminAddress) != true) {
        return false;
    }
    if (putData(_adminPort) != true) {
        return false;
    }
    if (putData(_adminDB) != true) {
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
    return _logPath.second.isEmpty() ? defaultLogPath() : _logPath.second.copy();
}

int32 D1ConfFileReader::logCounts() const
{
    const int32 hoursPerDay = 24;
    return hoursPerDay * (logDays() > 0 ? logDays() : defaultLogDays());
}
