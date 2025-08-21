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
        D1ServiceInfo(int32 serviceID, int32 buildNum, B1String&& addresses, B1String&& serviceName, B1String&& buildDate, B1String&& startTime, B1String&& systemID, B1String&& controllerVersion = "");
        D1ServiceInfo(D1ServiceInfo&& r) noexcept;
        virtual ~D1ServiceInfo();
    public:
        struct SERVICE_STATE : B1Object {
            enum ALIVE {
                ALIVE_NO = 0,
                ALIVE_YES = 1,

                ALIVE_DEFAULT = ALIVE_NO,
            };
            enum ON {
                ON_NO = 0,
                ON_YES = 1,

                ON_DEFAULT = ON_YES,
            };
            SERVICE_STATE();
            SERVICE_STATE(SERVICE_STATE&& r) noexcept;
            DataInt32 _alive;
            DataInt32 _on;
            DataMapInt32 _connections;  //  map<service_id, connection_state>. connection_state:1(connected)/0(disconnected)
            void archiveTo(B1Archive* archive) const final;
            void unarchiveFrom(const B1Archive& archive) final;
            B1String toString() const;
            bool isAlive() const { return _alive.second == ALIVE_YES; }
            bool isOn() const { return _on.second != ON_NO; }
            void setAlive(bool flag) { _alive.second = flag ? ALIVE_YES : ALIVE_NO; }
            void setOn(bool flag) { _on.second = flag ? ON_YES : ON_NO; }
        };
    protected:
        DataInt32 _serviceID;
        DataInt32 _buildNum;
        DataString _addresses;
        DataString _serviceName;
        DataString _buildDate;
        DataString _startTime;
        DataString _systemID;
        DataString _controllerVersion;
        std::pair<const B1String, SERVICE_STATE> _serviceState; //  store_in_redis seperately.
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
        const B1String& controllerVersion() const { return _controllerVersion.second; }
        bool isServiceStateAlive() const { return _serviceState.second.isAlive(); }
        bool isServiceStateOn() const { return _serviceState.second.isOn(); }
        void setServiceStateAlive(bool flag) { _serviceState.second.setAlive(flag); }
        void setServiceStateOn(bool flag) { _serviceState.second.setOn(flag); }
        void setServiceStateConnection(std::map<int32, int32>&& connections) { _serviceState.second._connections.second.swap(connections); }
        void addServiceStateConnection(int32 serviceID, int32 connection) { _serviceState.second._connections.second.insert(std::make_pair(serviceID, connection)); }
    };
}   //  !BnD

#endif  // !_D1DATA_SERVICE_INFO_H
