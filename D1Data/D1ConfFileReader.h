//
// D1ConfFileReader.h
//
// Library: D1Data
// Package: D1Data
// Module:  D1Data
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1DATA_CONF_FILE_READER_H
#define _D1DATA_CONF_FILE_READER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Data/D1RawFileReader.h>

namespace BnD {
    class D1ConfFileReader : public D1RawFileReader {
    public:
        D1ConfFileReader();
        virtual ~D1ConfFileReader();
    protected:
        DataString _logPath;
        DataString _adminAddress;
        DataInt32 _logDays;
        DataInt32 _adminPort;
        DataInt32 _adminDB;
    protected:
        virtual B1String implConfigFilePath() const;
        virtual B1String defaultLogPath() const;
        virtual int32 defaultLogDays() const;
    protected:
        virtual B1String implToString() const override;
        virtual bool validate() const override;
        virtual bool readData() override;
        virtual bool writeData() override;
    public:
        B1String configFilePath() const;
        bool loadDefault();
        bool saveDefault();
        const B1String& adminAddress() const { return _adminAddress.second; }
        B1String logPath() const;
        int32 logCounts() const;
        int32 logDays() const { return _logDays.second; }
        int32 adminPort() const { return _adminPort.second; }
        int32 adminDB() const { return _adminDB.second; }

        void setLogPath(B1String&& path) { _logPath.second = std::move(path); }
        void setAdminAddress(B1String&& address) { _adminAddress.second = std::move(address); }
        void setLogDays(int32 days) { _logDays.second = days; }
        void setAdminPort(int32 port) { _adminPort.second = port; }
        void setAdminDB(int32 db) { _adminDB.second = db; }
    };
}   //  !BnD

#endif  // !_D1DATA_CONF_FILE_READER_H
