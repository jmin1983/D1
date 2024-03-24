//
// D1BaseClient.h
//
// Library: D1Network
// Package: D1Network
// Module:  D1Network
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1NETWORK_BASE_CLIENT_H
#define _D1NETWORK_BASE_CLIENT_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <B1Network/B1BaseClient.h>

#include <set>

namespace BnD {
    class D1BasePacketMaker;
    class D1BaseClient : protected B1BaseClient {
    public:
        D1BaseClient(int32 maxAliveCount, int32 aliveInterval);   //  server로 alive_check 요청.
        virtual ~D1BaseClient();
    public:
        enum SEND_RESULT {
            SEND_RESULT_SUCCESS = 0,
            SEND_RESULT_NO_ID_FOUND,
            SEND_RESULT_NETWORK_ERROR,
        };
    protected:
        const int32 _maxAliveCount;
        const int32 _aliveInterval;
        std::shared_ptr<D1BasePacketMaker> _packetMaker;
    protected:
        virtual bool implInitialize() { return true; }
        virtual void implFinalize() {}
        virtual B1BaseClientSession* createD1BaseClientSession(B1ClientSocket* clientSocket);
    protected:
        virtual B1BaseSessionManager* createSessionManager() override;
        virtual B1BaseClientSession* createSession(B1ClientSocket* clientSocket, void* param) override;
    protected:
        int32 connectionStatus(int32 id) const;
    public:
        D1BasePacketMaker* packetMaker() const { return _packetMaker.get(); }
        bool initialize();
        void finalize();
        bool connect(const B1String& address, uint16 port, int32 id);
        bool isConnected(int32 id, int32* reason = NULL) const;
        SEND_RESULT sendTextMessage(int32 id, const B1String& message);
        void sendTextMessageToAllSessions(const B1String& message, std::set<int32>* sentIDs);
    };
}   //  !BnD

#endif  // !_D1NETWORK_BASE_CLIENT_H
