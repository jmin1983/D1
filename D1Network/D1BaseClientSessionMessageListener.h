//
// D1BaseClientSessionMessageListener.h
//
// Library: D1Network
// Package: D1Network
// Module:  D1Network
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1NETWORK_BASE_CLIENT_SESSION_MESSAGE_LISTENER_H
#define _D1NETWORK_BASE_CLIENT_SESSION_MESSAGE_LISTENER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

namespace BnD {
    class D1BaseClientSessionMessageListener {
    public:
        virtual void onClientSessionConnected() {}
        virtual void onRecvClientDataTextMessage(B1String&& message) {}
        virtual void onRecvClientDataTextMessageBunch(int32 index, int32 indexCount, B1String&& message) {}
        virtual void onRecvClientDataBinary(int32 index, int32 indexCount, std::vector<uint8>&& binaryData) {}
    };
}   //  !BnD

#endif  // !_D1NETWORK_BASE_CLIENT_SESSION_MESSAGE_LISTENER_H
