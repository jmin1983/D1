//
// D1BaseClientSession.h
//
// Library: D1Network
// Package: D1Network
// Module:  D1Network
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1NETWORK_BASE_CLIENT_SESSION_H
#define _D1NETWORK_BASE_CLIENT_SESSION_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif
 
#include <B1Network/B1ArrayBufferClientSession.h>
#include <D1Network/D1BasePacketAnalyzer.h>

namespace BnD {
    class D1BaseClientSessionMessageListener;
    class D1BasePacketMaker;
    class D1BaseClientSession : protected D1BasePacketAnalyzer
                              , public B1ArrayBufferClientSession {
    public:
        D1BaseClientSession(int32 clientID, B1ClientSocket* clientSocket, B1BaseClientSessionListener* listener, D1BasePacketMaker* packetMaker, int32 maxAliveCount,
                            D1BaseClientSessionMessageListener* messageListener = NULL, size_t defaultBufferSize = CONSTS_DEFAULT_BUFFER_RESERVED_SIZE);
        virtual ~D1BaseClientSession();
    private:
        const int32 _maxAliveCount;
        int32 _aliveCheckCount;
        uint64 _lastReconnectTick;
        uint64 _nextReconnectInterval;
    protected:
        const int32 _clientID;
        D1BasePacketMaker* _packetMaker;
        D1BaseClientSessionMessageListener* _messageListener;
    protected:  //  D1BasePacketAnalyzer
        void implOnProtocolTypeAliveCheck() final;
        virtual void implOnProtocolTypeTextMessage(B1String&& message) override;
        virtual void implOnProtocolTypeTextMessageBunch(int32 index, int32 indexCount, B1String&& message) override;
        virtual void implOnProtocolTypeBinary(int32 index, int32 indexCount, std::vector<uint8>&& binaryData) override;
    protected:  //  B1BaseClientSession
        void onReadComplete(uint8* data, size_t dataSize) final;
        virtual void implOnConnect() override;
        virtual void implProcessConnected(bool firstConnectedProcess) override;
        virtual void implProcessDisconnected() override;
    protected:
        int64 generateNextReconnectInterval() const;
    protected:
        D1BasePacketMaker* packetMaker() const { return _packetMaker; }
        void resetAliveCheckCount();
    public:
        bool sendData(const std::vector<uint8>& data);
    };
}   //  !BnD

#endif  // !_D1NETWORK_BASE_CLIENT_SESSION_H
