//
// D1BasePacketAnalyzer.h
//
// Library: D1Network
// Package: D1Network
// Module:  D1Network
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1NETWORK_BASE_PACKET_ANALYZER_H
#define _D1NETWORK_BASE_PACKET_ANALYZER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <B1Network/B1BasePacketAnalyzer.h>

namespace BnD {
    class D1BasePacketAnalyzer : public B1BasePacketAnalyzer {
    protected:
        virtual void implOnProtocolTypeAliveCheck() {}
        virtual void implOnProtocolTypeNotifyID(int32 id) {}
        virtual void implOnProtocolTypeTextMessage(B1String&& message) {}
        virtual void implOnProtocolTypeTextMessageBunch(int32 index, int32 indexCount, B1String&& message) {}
        virtual void implOnProtocolTypeBinary(int32 index, int32 indexCount, std::vector<uint8>&& binaryData) {}
    protected:
        ANALYZE_RESULT implAnalyzeData(uint8* data, size_t size, size_t* pos) final;
    protected:
        ANALYZE_RESULT analyzeProtocolTypeNotifyID(uint8* data, size_t size, size_t* pos);
        ANALYZE_RESULT analyzeProtocolTypeTextMessage(uint8* data, size_t size, size_t* pos);
        ANALYZE_RESULT analyzeProtocolTypeTextMessageBunch(uint8* data, size_t size, size_t* pos);
        ANALYZE_RESULT analyzeProtocolTypeBinary(uint8* data, size_t size, size_t* pos);
    };
}   //  !BnD

#endif  // !_D1NETWORK_BASE_PACKET_ANALYZER_H
