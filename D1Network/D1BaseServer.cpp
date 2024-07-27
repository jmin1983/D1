//
// D1BaseServer.cpp
//
// Library: D1Network
// Package: D1Network
// Module:  D1Network
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Network.h"
#include "D1BaseServer.h"
#include "D1BaseServerSession.h"
#include "D1BaseServerHandleManager.h"
#include "D1BasePacketMaker.h"

#include <B1Network/B1BaseSessionManager.h>

using namespace BnD;

D1BaseServer::D1BaseServer(int32 maxAliveCount, int32 aliveInterval)
    : B1BaseServer()
    , _maxAliveCount(maxAliveCount)
    , _aliveInterval(aliveInterval)
    , _handleManager(new D1BaseServerHandleManager())
    , _packetMaker(new D1BasePacketMaker())
{
}

D1BaseServer::~D1BaseServer()
{
}

auto D1BaseServer::createSessionManager() -> B1BaseSessionManager*
{
    return new B1BaseSessionManager(_aliveInterval);
}

auto D1BaseServer::createSession(B1ServerSocket* serverSocket) -> B1BaseServerSession*
{
    return new D1BaseServerSession(serverSocket, this, this, _maxAliveCount);
}

bool D1BaseServer::initialize(int32 port)
{
    if (port < 1 || port > UINT16_MAX) {
        return false;
    }
    if (startup() != true) {
        return false;
    }
    if (accept(static_cast<uint16>(port)) != true) {
        return false;
    }
    return implInitialize();
}

void D1BaseServer::finalize()
{
    implFinalize();
    close();
    shutdown();
}

auto D1BaseServer::sendTextMessage(int32 id, const B1String& message) -> SEND_RESULT
{
    const int32 handleID = _handleManager->getServerHandleID(id);
    if (auto session = sessionManager()->getSessionByHandleID<D1BaseServerSession>(handleID)) {
        if (session->sendData(packetMaker()->makeDataTextMessage(message)) != true) {
            return SEND_RESULT_NETWORK_ERROR;
        }
        return SEND_RESULT_SUCCESS;
    }
    else {
        return SEND_RESULT_NO_ID_FOUND;
    }
}

auto D1BaseServer::sendTextMessageBunch(int32 id, int32 index, int32 indexCount, const B1String& message) -> SEND_RESULT
{
    const int32 handleID = _handleManager->getServerHandleID(id);
    if (auto session = sessionManager()->getSessionByHandleID<D1BaseServerSession>(id)) {
        if (session->sendData(packetMaker()->makeDataTextMessageBunch(index, indexCount, message)) != true) {
            return SEND_RESULT_NETWORK_ERROR;
        }
        return SEND_RESULT_SUCCESS;
    }
    else {
        return SEND_RESULT_NO_ID_FOUND;
    }
}

bool D1BaseServer::containsID(int32 id) const
{
    return _handleManager->containsID(id);
}

void D1BaseServer::sendTextMessageToAllSessions(const B1String& message, std::set<int32>* sentIDs)
{
    auto sessions = sessionManager()->getAllSessions();
    if (sessions.empty()) {
        return;
    }
    auto packet = packetMaker()->makeDataTextMessage(message);
    for (const auto& sessionsPair : sessions) {
        if (auto session = std::dynamic_pointer_cast<D1BaseServerSession>(sessionsPair.second._session)) {
            if (session->sendData(packet)) {
                if (sentIDs) {
                    sentIDs->insert(session->id());
                }
            }
            else {
                B1LOG("send all server sesssion failed: id[%d]", session->id());
            }
        }
        else {
            B1LOG("invalid session found in send all server sessions");
        }
    }
}
