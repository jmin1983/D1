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
    class D1BasePacketMaker;
    class D1BaseClientSession : protected D1BasePacketAnalyzer
                              , public B1ArrayBufferClientSession {
    public:
        D1BaseClientSession(B1ClientSocket* clientSocket, B1BaseClientSessionListener* listener, D1BasePacketMaker* packetMaker, int32 maxAliveCount);
        virtual ~D1BaseClientSession();
    private:
        const int32 _maxAliveCount;
        int32 _aliveCheckCount;
        uint64 _lastReconnectTick;
    protected:
        D1BasePacketMaker* _packetMaker;
    protected:  //  D1BasePacketAnalyzer
        void implOnProtocolTypeAliveCheck() final;
    protected:  //  B1BaseClientSession
        void onReadComplete(uint8* data, size_t dataSize) final;
        virtual void implOnConnect() override;
        virtual void implProcessConnected(bool firstConnectedProcess) override;
        virtual void implProcessDisconnected() override;
    protected:
        D1BasePacketMaker* packetMaker() const { return _packetMaker; }
    public:
        bool sendData(const std::vector<uint8>& data);
    };
}   //  !BnD

#endif  // !_D1NETWORK_BASE_CLIENT_SESSION_H
