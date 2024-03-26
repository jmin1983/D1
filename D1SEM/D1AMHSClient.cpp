//
// D1AMHSClient.cpp
//
// Library: D1SEM
// Package: AMHS
// Module:  D1SEM
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1SEM.h"
#include "D1AMHSClient.h"
#include "D1AMHSClientListener.h"
#include "D1AMHSClientSession.h"
#include "D1AMHSDataManager.h"

#include <B1Network/B1BaseSessionManager.h>
#include <B1Network/B1NetworkTypeConverter.h>

using namespace BnD;

D1AMHSClient::D1AMHSClient(const D1AMHSDataManager* secs2DataManager, D1AMHSClientListener* listener)
    : B1SECS2Client(secs2DataManager)
    , _listener(listener)
{
}

B1BaseClientSession* D1AMHSClient::createSession(B1ClientSocket* clientSocket, void* param)
{
    return new D1AMHSClientSession(clientSocket, this, *(uint16*)param, static_cast<const D1AMHSDataManager*>(_secs2DataManager), _listener);
}

bool D1AMHSClient::requestOnline(uint16 deviceID)
{
    return sendMessageS1F13(deviceID);
}
