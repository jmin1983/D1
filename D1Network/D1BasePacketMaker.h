//
// D1BasePacketMaker.h
//
// Library: D1Network
// Package: D1Network
// Module:  D1Network
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1NETWORK_BASE_PACKET_MAKER_H
#define _D1NETWORK_BASE_PACKET_MAKER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

namespace BnD {
    class D1BasePacketMaker {
    public:
        D1BasePacketMaker();
        virtual ~D1BasePacketMaker();
    public:
        std::vector<uint8> makeDataNotifyID(int32 id);
        std::vector<uint8> makeDataTextMessage(const B1String& message);
        std::vector<uint8> makeDataTextMessageBunch(int32 index, int32 indexCount, const B1String& message);
        std::vector<uint8> makeDataBinary(int32 index, int32 indexCount, const std::vector<uint8>& data);
    };
}   //  !BnD

#endif  // !_D1NETWORK_BASE_PACKET_MAKER_H
