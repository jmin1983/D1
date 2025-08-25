//
// D1SMSServer.h
//
// Library: D1Service
// Package: SMS
// Module:  D1Service
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1SERVICE_SMS_SERVER_H
#define _D1SERVICE_SMS_SERVER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Network/D1BaseServer.h>

namespace BnD {
    class D1SMSPacketMaker;
    class D1SMSServerSessionDelegate;
    class D1SMSServer : public D1BaseServer {
    public:
        D1SMSServer(D1SMSServerSessionDelegate* smsServerDelegate);
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
        D1SMSServerSessionDelegate* _smsServerDelegate;
    protected:
        D1BasePacketMaker* createPacketMaker() final;
        B1BaseServerSession* createSession(B1ServerSocket* serverSocket) final;
    };
}   //  !BnD

#endif  // !_D1SERVICE_SMS_SERVER_H
