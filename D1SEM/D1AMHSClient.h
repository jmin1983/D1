//
// D1AMHSClient.h
//
// Library: D1SEM
// Package: AMHS
// Module:  D1SEM
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1SEM_AMHS_CLIENT_H
#define _D1SEM_AMHS_CLIENT_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <B1SECS2/B1SECS2Client.h>

namespace BnD {
    class D1AMHSClientListener;
    class D1AMHSDataManager;
    class D1AMHSClient : public B1SECS2Client {
    public:
        D1AMHSClient(const D1AMHSDataManager* secs2DataManager, D1AMHSClientListener* listener = NULL);
    protected:
        D1AMHSClientListener* _listener;
    protected:
        virtual B1BaseClientSession* createSession(B1ClientSocket* clientSocket, void* param) override;
    public:
        bool requestOnline(uint16 deviceID);
    };
}   //  !BnD

#endif  // !_D1SEM_AMHS_CLIENT_H
