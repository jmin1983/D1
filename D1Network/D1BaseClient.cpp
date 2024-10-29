//
// D1BaseClient.cpp
//
// Library: D1Network
// Package: D1Network
// Module:  D1Network
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Network.h"
#include "D1BaseClient.h"
#include "D1BaseClientSession.h"
#include "D1BasePacketMaker.h"

#include <B1Network/B1BaseSessionManager.h>
#include <B1Network/B1NetworkTypeConverter.h>

using namespace BnD;

D1BaseClient::D1BaseClient(int32 clientID, int32 maxAliveCount, int32 aliveInterval)
    : B1BaseClient()
    , _maxAliveCount(maxAliveCount)
    , _aliveInterval(aliveInterval)
    , _clientID(clientID)
    , _packetMaker()
{
}

D1BaseClient::~D1BaseClient()
{
}

auto D1BaseClient::createPacketMaker() -> D1BasePacketMaker*
{
    return new D1BasePacketMaker();
}

auto D1BaseClient::createD1BaseClientSession(B1ClientSocket* clientSocket, void* param) -> B1BaseClientSession*
{
    return new D1BaseClientSession(_clientID, clientSocket, this, _packetMaker.get(), _maxAliveCount);
}

auto D1BaseClient::createSessionManager() -> B1BaseSessionManager*
{
    return new B1BaseSessionManager(_aliveInterval);
}

auto D1BaseClient::createSession(B1ClientSocket* clientSocket, void* param) -> B1BaseClientSession*
{
    return createD1BaseClientSession(clientSocket, param);
}

int32 D1BaseClient::connectionStatus(int32 id) const
{
    if (auto session = sessionManager()->getBaseSessionByHandleID(id)) {
        return session->currentConnectionStatus();
    }
    else {
        return B1BaseSession::STATUS_NONE;
    }
}

bool D1BaseClient::initialize()
{
    _packetMaker.reset(createPacketMaker());
    if (startup() != true) {
        return false;
    }
    srand((unsigned int)time(NULL));
    return implInitialize();
}

void D1BaseClient::finalize()
{
    implFinalize();
    shutdown();
    _packetMaker.reset();
}

bool D1BaseClient::connect(const B1String& address, uint16 port, int32 id, void* param)
{
    auto clientHandle = B1BaseClient::connect(address.copy(), port, param, id);
    if (0 == clientHandle) {
        B1LOG("unable to connect: address[%s], port[%d], id[%d]", address.cString(), port, id);
        return false;
    }
    return true;
}

bool D1BaseClient::isConnected(int32 id, int32* reason) const
{
    if (auto session = sessionManager()->getBaseSessionByHandleID(id)) {
        return session->isConnected();
    }
    else {
        if (reason) {
            *reason = SEND_RESULT_NO_ID_FOUND;
        }
        return false;
    }
}

auto D1BaseClient::sendTextMessage(int32 id, const B1String& message) -> SEND_RESULT
{
    if (auto session = sessionManager()->getSessionByHandleID<D1BaseClientSession>(id)) {
        if (session->sendData(packetMaker()->makeDataTextMessage(message)) != true) {
            return SEND_RESULT_NETWORK_ERROR;
        }
        return SEND_RESULT_SUCCESS;
    }
    else {
        return SEND_RESULT_NO_ID_FOUND;
    }
}

auto D1BaseClient::sendTextMessageBunch(int32 id, int32 index, int32 indexCount, const B1String& message) -> SEND_RESULT
{
    if (auto session = sessionManager()->getSessionByHandleID<D1BaseClientSession>(id)) {
        if (session->sendData(packetMaker()->makeDataTextMessageBunch(index, indexCount, message)) != true) {
            return SEND_RESULT_NETWORK_ERROR;
        }
        return SEND_RESULT_SUCCESS;
    }
    else {
        return SEND_RESULT_NO_ID_FOUND;
    }
}

void D1BaseClient::sendTextMessageToAllSessions(const B1String& message, std::set<int32>* sentIDs)
{
    auto sessions = sessionManager()->getAllSessions();
    if (sessions.empty()) {
        return;
    }
    auto packet = _packetMaker->makeDataTextMessage(message);
    for (const auto& sessionsPair : sessions) {
        if (auto session = std::dynamic_pointer_cast<D1BaseClientSession>(sessionsPair.second._session)) {
            if (session->sendData(packet)) {
                if (sentIDs) {
                    sentIDs->insert(session->sessionHandleID());
                }
            }
            else {
                B1LOG("send all client sesssions failed: id[%d]", session->sessionHandleID());
            }
        }
        else {
            B1LOG("invalid session found in send all client sessions");
        }
    }
}

auto D1BaseClient::sendBinary(int32 id, int32 index, int32 indexCount, const std::vector<uint8>& binaryData) -> SEND_RESULT
{
    if (auto session = sessionManager()->getSessionByHandleID<D1BaseClientSession>(id)) {
        if (session->sendData(packetMaker()->makeDataBinary(index, indexCount, binaryData)) != true) {
            return SEND_RESULT_NETWORK_ERROR;
        }
        return SEND_RESULT_SUCCESS;
    }
    else {
        return SEND_RESULT_NO_ID_FOUND;
    }
}
