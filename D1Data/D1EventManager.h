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
        D1EventManager();
        virtual ~D1EventManager();
    protected:
        D1RedisClientInterface* _redisClientInterface;
    public:
        void initialize(D1RedisClientInterface* redisClientInterface);
        void finalize();
        bool addEvent(int32 code, int32 serviceID, bool isEssential = false);
        bool addEvent(int32 code, int32 serviceID, int32 zoneID, bool isEssential = false);
        bool addEvent(int32 code, int32 serviceID, int32 zoneID, int64 taskID, int32 reason, bool isEssential = false);
        bool addEvent(int32 code, int32 serviceID, int32 zoneID, int64 taskID, int32 reason, B1String&& carrierID, bool isEssential = false);
    };
}   //  !BnD

#endif  // !_D1DATA_EVENT_MANAGER_H
