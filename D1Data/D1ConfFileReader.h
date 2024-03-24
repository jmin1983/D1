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
 
#include <boost/property_tree/ptree.hpp>

namespace BnD {
    class D1ConfFileReader {
    public:
        D1ConfFileReader();
        virtual ~D1ConfFileReader();
    protected:
        boost::property_tree::ptree _pt;
        B1String _logPath;
        B1String _redisAddress;
        int32 _logDays;
        int32 _redisPort;
        int32 _redisDB;
    protected:
        virtual B1String implToString() const;
        virtual B1String implConfigFilePath() const;
        virtual bool implLoad(const B1String& filePath);
        virtual bool implSave(const B1String& filePath);
        virtual bool validate() const;
        virtual bool readData();
        virtual bool writeData();
        virtual B1String defaultLogPath(const B1String& serviceNameInLowerCase) const;
        virtual int32 defaultLogDays() const;
    public:
        B1String toString() const;
        B1String configFilePath() const;
        bool load();
        bool load(const B1String& filePath);
        bool save(const B1String& filePath);
        const B1String &redisAddress() const { return _redisAddress; }
        B1String logPath(const B1String& serviceName) const;
        int32 logCounts() const;
        int32 redisPort() const { return _redisPort; }
        int32 redisDB() const { return _redisDB; }

        void setLogPath(B1String&& path) { _logPath = std::move(path); }
        void setRedisAddress(B1String&& address) { _redisAddress = std::move(address); }
        void setLogDays(int32 days) { _logDays = days; }
        void setRedisPort(int32 port) { _redisPort = port; }
        void setRedisDB(int32 db) { _redisDB = db; }
    };
}   //  !BnD

#endif  // !_D1DATA_CONF_FILE_READER_H
