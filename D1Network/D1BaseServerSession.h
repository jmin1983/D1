//
// D1BaseServerSession.h
//
// Library: D1Network
// Package: D1Network
// Module:  D1Network
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1NETWORK_BASE_SERVER_SESSION_H
#define _D1NETWORK_BASE_SERVER_SESSION_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif
 
#include <B1Network/B1ArrayBufferServerSession.h>
#include <D1Network/D1BasePacketAnalyzer.h>

namespace BnD {
    class D1BasePacketMaker;
    class D1BaseServer;
    class D1BaseServerSessionMessageListener;
    class D1BaseServerSession : protected D1BasePacketAnalyzer
                              , public B1ArrayBufferServerSession {
    public:
        D1BaseServerSession(B1ServerSocket* serverSocket, B1BaseServerSessionListener* listener, D1BaseServer* owner, int32 maxAliveCount,
                            D1BaseServerSessionMessageListener* messageListener = NULL, size_t defaultBufferSize = CONSTS_DEFAULT_BUFFER_RESERVED_SIZE);
        virtual ~D1BaseServerSession();
    private:
        const int32 _maxAliveCount;
        int32 _aliveCheckCount;
    protected:
        D1BaseServer* _owner;
        int32 _id;
        D1BaseServerSessionMessageListener* _messageListener;
    protected:  //  D1BasePacketAnalyzer
        void implOnProtocolTypeAliveCheck() final;
        virtual void implOnProtocolTypeNotifyID(int32 id) override;
        virtual void implOnProtocolTypeTextMessage(B1String&& message) override;
        virtual void implOnProtocolTypeTextMessageBunch(int32 index, int32 indexCount, B1String&& message) override;
        virtual void implOnProtocolTypeBinary(int32 index, int32 indexCount, std::vector<uint8>&& binaryData) override;
    protected:  //  B1BaseServerSession
        void onReadComplete(uint8* data, size_t dataSize) final;
        virtual void implOnServerSessionDisconnected(int32 reason) override;
        virtual void implProcessConnected(bool firstConnectedProcess) override;
    protected:
        D1BaseServer* owner() const { return _owner; }
        D1BasePacketMaker* packetMaker() const;
        void resetAliveCheckCount();
    public:
        bool sendData(const std::vector<uint8>& data);
        bool isValidID() const;
        int32 id() const { return _id; }
    };
}   //  !BnD

#endif  // !_D1NETWORK_BASE_SERVER_SESSION_H
