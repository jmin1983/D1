//
// D1SMSServer.cpp
//
// Library: D1Service
// Package: SMS
// Module:  D1Service
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Service.h"
#include "D1SMSServer.h"
#include "D1SMSPacketMaker.h"
#include "D1SMSServerSession.h"
#include "D1SMSServerSessionDelegate.h"

#include <B1Network/B1BaseSessionManager.h>

using namespace BnD;

D1SMSServer::D1SMSServer(D1SMSServerSessionDelegate* smsServerDelegate)
    : D1BaseServer(CONSTS_ALIVE_COUNT, CONSTS_ALIVE_INTERVAL)
    , _smsServerDelegate(smsServerDelegate)
{
}

auto D1SMSServer::createPacketMaker() -> D1BasePacketMaker*
{
    return new D1SMSPacketMaker();
}

auto D1SMSServer::createSession(B1ServerSocket* serverSocket) -> B1BaseServerSession*
{
    return new D1SMSServerSession(serverSocket, this, this, _maxAliveCount, _smsServerDelegate);
}
