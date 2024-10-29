//
// D1ServiceInfo.h
//
// Library: D1Data
// Package: D1Data
// Module:  D1Data
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1DATA_SERVICE_INFO_H
#define _D1DATA_SERVICE_INFO_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <B1Base/B1Object.h>

#include <D1Data/D1RedisHashmapObject.h>

namespace BnD {
    class D1ServiceInfo : public B1Object 
                        , public D1RedisHashmapObject {
    public:
        D1ServiceInfo();
        D1ServiceInfo(int32 serviceID, B1String&& serviceName);
        D1ServiceInfo(int32 serviceID, int32 buildNum, B1String&& addresses, B1String&& serviceName, B1String&& buildDate, B1String&& startTime, B1String&& systemID);
        D1ServiceInfo(D1ServiceInfo&& r) noexcept;
        virtual ~D1ServiceInfo();
    protected:
        DataInt32 _serviceID;
        DataInt32 _buildNum;
        DataString _addresses;
        DataString _serviceName;
        DataString _buildDate;
        DataString _startTime;
        DataString _systemID;
    protected:
        virtual void archiveTo(B1Archive* archive) const override;
        virtual void unarchiveFrom(const B1Archive& archive) override;
    protected:
        virtual B1String redisKey() const override;
        virtual bool isValidToMakeRedisString() const override;
        virtual void makeRedisStringArgs(std::vector<B1String>* args) const override;
        virtual bool readRedisMap(const std::map<B1String, B1String>& map) override;
    public:
        virtual B1String toString() const;
    public:
        int32 serviceID() const { return _serviceID.second; }
        int32 buildNum() const { return _buildNum.second; }
        const B1String& addresses() const { return _addresses.second; }
        const B1String& serviceName() const { return _serviceName.second; }
        const B1String& buildDate() const { return _buildDate.second; }
        const B1String& startTime() const { return _startTime.second; }
        const B1String& systemID() const { return _systemID.second; }
    };
}   //  !BnD

#endif  // !_D1DATA_SERVICE_INFO_H
