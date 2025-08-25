//
// D1SMSClient.cpp
//
// Library: D1Service
// Package: SMS
// Module:  D1Service
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Service.h"
#include "D1SMSClient.h"
#include "D1SMSClientSession.h"
#include "D1SMSPacketMaker.h"

#include <B1Network/B1BaseSessionManager.h>

using namespace BnD;

D1SMSClient::D1SMSClient(int32 clientID)
    : D1BaseClient(clientID, CONSTS_ALIVE_COUNT, CONSTS_ALIVE_INTERVAL)
    , _listener(NULL)
{
}

D1SMSClient::~D1SMSClient()
{
}

auto D1SMSClient::createPacketMaker() -> D1BasePacketMaker*
{
    return new D1SMSPacketMaker();
}

auto D1SMSClient::createD1BaseClientSession(B1ClientSocket* clientSocket, void* param) -> B1BaseClientSession*
{
    return new D1SMSClientSession(_clientID, clientSocket, this, packetMaker(), _maxAliveCount, _listener);
}

auto D1SMSClient::packetMaker() const -> D1SMSPacketMaker*
{
    return static_cast<D1SMSPacketMaker*>(D1BaseClient::packetMaker());
}

bool D1SMSClient::initialize(const B1String& address, uint16 port, D1SMSClientSessionListener* listener)
{
    _listener = listener;
    if (D1BaseClient::initialize() != true) {
        _listener = NULL;
        return false;
    }
    if (D1BaseClient::connect(address.copy(), port, _clientID) != true) {
        _listener = NULL;
        return false;
    }
    return true;
}

void D1SMSClient::finalize()
{
    D1BaseClient::finalize();
    _listener = NULL;
}

bool D1SMSClient::isDisconnected() const
{
    auto session = sessionManager()->getUniqueSession<D1SMSClientSession>();
    return session ? session->isDisconnected() : false;
}

bool D1SMSClient::sendDropCacheMemoryNtf()
{
    auto session = sessionManager()->getUniqueSession<D1SMSClientSession>();
    return session ? session->sendDropCacheMemoryNtf() : false;
}

bool D1SMSClient::sendRebootSystemNtf()
{
    auto session = sessionManager()->getUniqueSession<D1SMSClientSession>();
    return session ? session->sendRebootSystemNtf() : false;
}

bool D1SMSClient::sendHostAddressesReq()
{
    auto session = sessionManager()->getUniqueSession<D1SMSClientSession>();
    return session ? session->sendHostAddressesReq() : false;
}

bool D1SMSClient::sendHostNameReq()
{
    auto session = sessionManager()->getUniqueSession<D1SMSClientSession>();
    return session ? session->sendHostNameReq() : false;
}

bool D1SMSClient::sendSystemResourceUsagesReq()
{
    auto session = sessionManager()->getUniqueSession<D1SMSClientSession>();
    return session ? session->sendSystemResourceUsagesReq() : false;
}

bool D1SMSClient::sendStartSystemServiceReq(const B1String& name)
{
    auto session = sessionManager()->getUniqueSession<D1SMSClientSession>();
    return session ? session->sendStartSystemServiceReq(name) : false;
}

bool D1SMSClient::sendStopSystemServiceReq(const B1String& name)
{
    auto session = sessionManager()->getUniqueSession<D1SMSClientSession>();
    return session ? session->sendStopSystemServiceReq(name) : false;
}

bool D1SMSClient::sendStatusSystemServiceReq(const B1String& name)
{
    auto session = sessionManager()->getUniqueSession<D1SMSClientSession>();
    return session ? session->sendStatusSystemServiceReq(name) : false;
}
