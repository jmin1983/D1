//
// D1BaseClientSession.cpp
//
// Library: D1Network
// Package: D1Network
// Module:  D1Network
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Network.h"
#include "D1BaseClientSession.h"
#include "D1BaseClientSessionMessageListener.h"
#include "D1BaseProtocol.h"
#include "D1BasePacketMaker.h"

#include <B1Base/B1TickUtil.h>

using namespace BnD;

D1BaseClientSession::D1BaseClientSession(int32 clientID, B1ClientSocket* clientSocket, B1BaseClientSessionListener* listener, D1BasePacketMaker* packetMaker, int32 maxAliveCount,
                                         D1BaseClientSessionMessageListener* messageListener, size_t defaultBufferSize)
    : D1BasePacketAnalyzer(defaultBufferSize)
    , B1ArrayBufferClientSession(clientSocket, listener)
    , _maxAliveCount(maxAliveCount)
    , _aliveCheckCount(0)
    , _lastReconnectTick(0)
    , _nextReconnectInterval(generateNextReconnectInterval())
    , _clientID(clientID)
    , _packetMaker(packetMaker)
    , _messageListener(messageListener)
{
}

D1BaseClientSession::~D1BaseClientSession()
{
}

void D1BaseClientSession::implOnProtocolTypeAliveCheck()
{
    _aliveCheckCount = 0;
}

void D1BaseClientSession::implOnProtocolTypeTextMessage(B1String&& message)
{
    if (_messageListener) {
        _messageListener->onRecvClientDataTextMessage(std::move(message));
    }
}

void D1BaseClientSession::implOnProtocolTypeTextMessageBunch(int32 index, int32 indexCount, B1String&& message)
{
    if (_messageListener) {
        _messageListener->onRecvClientDataTextMessageBunch(index, indexCount, std::move(message));
    }
}

void D1BaseClientSession::implOnProtocolTypeBinary(int32 index, int32 indexCount, std::vector<uint8>&& binaryData)
{
    if (_messageListener) {
        _messageListener->onRecvClientDataBinary(index, indexCount, std::move(binaryData));
    }
}

void D1BaseClientSession::onReadComplete(uint8* data, size_t dataSize)
{
    if (analyzeData(data, dataSize) != true) {
        disconnect();
    }
}

void D1BaseClientSession::implOnConnect()
{
    B1LOG("session connected -> clear buffer: id:[%d]", sessionHandleID());
    _aliveCheckCount = 0;
    clearBuffer();
    B1ArrayBufferClientSession::implOnConnect();
}

void D1BaseClientSession::implProcessConnected(bool firstConnectedProcess)
{
    if (firstConnectedProcess) {
        sendData(packetMaker()->makeDataNotifyID(_clientID));
    }
    else {
        D1BaseProtocol::Header header(D1BaseProtocol::Header::TYPE_ALIVE_CHECK);
        writeData((const uint8*)&header, sizeof(header));
        if (++_aliveCheckCount > _maxAliveCount) {
            B1LOG("alive check failed -> client force to disconnect: id[%d], aliveCheckCount[%d], maxAliveCount[%d]", sessionHandleID(), _aliveCheckCount, _maxAliveCount);
            disconnect();
        }
    }
    if (firstConnectedProcess && _messageListener) {
        _messageListener->onClientSessionConnected();
    }
}

void D1BaseClientSession::implProcessDisconnected()
{
    uint64 now = B1TickUtil::currentTick();
    if (B1TickUtil::diffTick(_lastReconnectTick, now) >= _nextReconnectInterval) {
        _lastReconnectTick = now;
        _nextReconnectInterval = generateNextReconnectInterval();
        reconnect();
    }
}

int64 D1BaseClientSession::generateNextReconnectInterval() const
{
    int64 min = D1BaseProtocol::CONSTS_CLIENT_RECONNECT_INTERVAL_MIN;
    int64 max = D1BaseProtocol::CONSTS_CLIENT_RECONNECT_INTERVAL_MAX;
    return (rand() % (max - min)) + min;
}

bool D1BaseClientSession::sendData(const std::vector<uint8>& data)
{
    return writeData(data);
}
