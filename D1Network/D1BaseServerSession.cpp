//
// D1BaseServerSession.cpp
//
// Library: D1Network
// Package: D1Network
// Module:  D1Network
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Network.h"
#include "D1BaseServerSession.h"
#include "D1BaseProtocol.h"
#include "D1BaseServer.h"
#include "D1BaseServerHandleManager.h"

using namespace BnD;

D1BaseServerSession::D1BaseServerSession(B1ServerSocket* serverSocket, B1BaseServerSessionListener* listener, D1BaseServer* owner, int32 maxAliveCount)
    : B1ArrayBufferServerSession(serverSocket, listener)
    , _maxAliveCount(maxAliveCount)
    , _aliveCheckCount(0)
    , _owner(owner)
    , _id(-1)
{
}

D1BaseServerSession::~D1BaseServerSession()
{
}

void D1BaseServerSession::implOnProtocolTypeAliveCheck()
{
    _aliveCheckCount = 0;
    D1BaseProtocol::Header header(D1BaseProtocol::Header::TYPE_ALIVE_CHECK);
    writeData((const uint8*)&header, sizeof(header));
}

void D1BaseServerSession::implOnProtocolTypeNotifyID(int32 id)
{
    if (id < 0) {
        B1LOG("invalid handle notified -> disconnect: id[%d]", id);
        disconnect();
        return;
    }
    B1LOG("add handle: id[%d]", id);
    if (owner()->handleManager()->addID(id, sessionHandleID()) != true) {
        B1LOG("already added handle -> disconnect: id[%d]", id);
        disconnect();
        return;
    }
    _id = id;
}

void D1BaseServerSession::onReadComplete(uint8* data, size_t dataSize)
{
    if (analyzeData(data, dataSize) != true) {
        disconnect();
    }
}

void D1BaseServerSession::implOnDisconnected(int32 reason)
{
    B1LOG("remove handle: id[%d]", _id);
    if (_id > -1) {
        owner()->handleManager()->removeID(_id);
    }
    B1ArrayBufferServerSession::implOnDisconnected(reason);
}

void D1BaseServerSession::implProcessConnected(bool firstConnectedProcess)
{
    if (_id < 0) {
        const int32 maxAliveCountTimes = 10;
        if (++_aliveCheckCount > _maxAliveCount * maxAliveCountTimes) {
            B1LOG("set id timedout -> server force to disconnect: id[%d], aliveInterval[%d], aliveCheckCount[%d], maxAliveCount[%d]",
                  _id, owner()->aliveInterval(), _aliveCheckCount, _maxAliveCount * maxAliveCountTimes);
            disconnect();
        }
        return;
    }
    if (++_aliveCheckCount > _maxAliveCount) {
        B1LOG("alive check failed -> server force to disconnect: id[%d], aliveInterval[%d], aliveCheckCount[%d], maxAliveCount[%d]",
              _id, owner()->aliveInterval(), _aliveCheckCount, _maxAliveCount);
        disconnect();
    }
}

D1BasePacketMaker* D1BaseServerSession::packetMaker() const
{
    return owner()->packetMaker();
}

bool D1BaseServerSession::sendData(const std::vector<uint8>& data)
{
    if (_id < 0) {
        B1LOG("invalid session id. ignore sendData: address[%s]", peerAddress().cString());
        return false;
    }
    return writeData(data);
}
