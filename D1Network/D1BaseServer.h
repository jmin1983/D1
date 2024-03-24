//
// D1BaseServer.h
//
// Library: D1Network
// Package: D1Network
// Module:  D1Network
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1NETWORK_BASE_SERVER_H
#define _D1NETWORK_BASE_SERVER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <B1Network/B1BaseServer.h>

#include <set>

namespace BnD {
    class D1BaseServerHandleManager;
    class D1BasePacketMaker;
    class D1BaseServer : protected B1BaseServer {
    public:
        D1BaseServer(int32 maxAliveCount, int32 aliveInterval);  //  aliveInterval alive 검사. maxAliveCount를 넘어서면 timedout처리.
        virtual ~D1BaseServer();
    public:
        enum SEND_RESULT {
            SEND_RESULT_SUCCESS = 0,
            SEND_RESULT_NO_ID_FOUND,
            SEND_RESULT_NETWORK_ERROR,
        };
    protected:
        const int32 _maxAliveCount;
        const int32 _aliveInterval;
        std::shared_ptr<D1BaseServerHandleManager> _handleManager;
        std::shared_ptr<D1BasePacketMaker> _packetMaker;
    protected:
        virtual bool implInitialize() { return true; }
        virtual void implFinalize() {}
    protected:
        virtual B1BaseSessionManager* createSessionManager() override;
        virtual B1BaseServerSession* createSession(B1ServerSocket* serverSocket) override;
    public:
        D1BaseServerHandleManager* handleManager() const { return _handleManager.get(); }
        D1BasePacketMaker* packetMaker() const { return _packetMaker.get(); }
        bool initialize(int32 port);
        void finalize();
        SEND_RESULT sendTextMessage(int32 id, const B1String& message);
        int32 aliveInterval() const { return _aliveInterval; }
        bool containsID(int32 id) const;
        void sendTextMessageToAllSessions(const B1String& message, const std::set<int32>& exceptIDs, std::set<int32>* sentIDs);
    };
}   //  !BnD

#endif  // !_D1NETWORK_BASE_SERVER_H
