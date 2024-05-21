//
// D1EventManager.h
//
// Library: D1Data
// Package: D1Data
// Module:  D1Data
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1DATA_EVENT_MANAGER_H
#define _D1DATA_EVENT_MANAGER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <B1Base/B1Singleton.h>

namespace BnD {
    class D1RedisClientInterface;
    class D1EventManager : public B1Singleton<D1EventManager> {
    public:
        D1EventManager(B1String&& channel);
        virtual ~D1EventManager();
    protected:
        const B1String _channel;
        D1RedisClientInterface* _redisClientInterface;
    protected:
        virtual int64 implMakeNewSerialNumber();
    protected:
        int64 makeNewSerialNumber();
        bool getTaskTransferInfo(int32 taskID, B1String* commandID, B1String* carrierID);
    public:
        void initialize(D1RedisClientInterface* redisClientInterface);
        void finalize();
        bool addEvent(int32 code, const B1String& commandID, const B1String& carrierID, int32 taskID, int32 zoneID, int32 reason, bool isEssential = false);
        bool addEvent(int32 code);
        bool addEvent(int32 code, int32 zoneID);
        bool addEvent(int32 code, int32 taskID, int32 zoneID, int32 reason, bool isEssential = false);
    };
}   //  !BnD

#endif  // !_D1DATA_EVENT_MANAGER_H
