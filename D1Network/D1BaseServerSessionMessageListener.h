//
// D1BaseServerSessionMessageListener.h
//
// Library: D1Network
// Package: D1Network
// Module:  D1Network
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1NETWORK_BASE_SERVER_SESSION_MESSAGE_LISTENER_H
#define _D1NETWORK_BASE_SERVER_SESSION_MESSAGE_LISTENER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

namespace BnD {
    class D1BaseServerSessionMessageListener {
    public:
        virtual void onRecvServerDataTextMessage(B1String&& message) {}
        virtual void onRecvServerDataTextMessageBunch(int32 index, int32 indexCount, B1String&& message) {}
        virtual void onRecvServerDataBinary(int32 index, int32 indexCount, std::vector<uint8>&& binaryData) {}
    };
}   //  !BnD

#endif  // !_D1NETWORK_BASE_SERVER_SESSION_MESSAGE_LISTENER_H
