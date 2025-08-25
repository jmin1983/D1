//
// D1SMSClient.h
//
// Library: D1Service
// Package: SMS
// Module:  D1Service
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1SERVICE_SMS_CLIENT_H
#define _D1SERVICE_SMS_CLIENT_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Network/D1BaseClient.h>

namespace BnD {
    class D1SMSClientSessionListener;
    class D1SMSPacketMaker;
    class D1SMSClient : protected D1BaseClient {
    public:
        D1SMSClient(int32 clientID);
        virtual ~D1SMSClient();
    protected:
        enum CONSTS {
#if defined(_DEBUG)
            CONSTS_ALIVE_COUNT = 60 * 30,
#else
            CONSTS_ALIVE_COUNT = 5,
#endif
            CONSTS_ALIVE_INTERVAL = 1000,
        };
    protected:
        D1SMSClientSessionListener* _listener;
    protected:
        D1BasePacketMaker* createPacketMaker() final;
        B1BaseClientSession* createD1BaseClientSession(B1ClientSocket* clientSocket, void* param) final;
    public:
        D1SMSPacketMaker* packetMaker() const;
        bool initialize(const B1String& address, uint16 port, D1SMSClientSessionListener* listener);
        void finalize();
        bool isDisconnected() const;
        bool sendDropCacheMemoryNtf();
        bool sendRebootSystemNtf();
        bool sendHostAddressesReq();
        bool sendHostNameReq();
        bool sendSystemResourceUsagesReq();
        bool sendStartSystemServiceReq(const B1String& name);
        bool sendStopSystemServiceReq(const B1String& name);
        bool sendStatusSystemServiceReq(const B1String& name);
    };
}   //  !BnD

#endif  // !_D1SERVICE_SMS_CLIENT_H
