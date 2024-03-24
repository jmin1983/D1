//
// D1BaseProtocol.h
//
// Library: D1Network
// Package: D1Network
// Module:  D1Network
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1NETWORK_BASE_PROTOCOL_H
#define _D1NETWORK_BASE_PROTOCOL_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

namespace BnD {
    namespace D1BaseProtocol {
        enum CONSTS {
            CONSTS_CLIENT_RECONNECT_INTERVAL = 1000,
        };
#pragma pack(1)
        struct Header {
            enum TYPE {
                TYPE_UNKNOWN = 0,
                TYPE_ALIVE_CHECK,
                TYPE_NOTIFY_ID,
                TYPE_TEXT_MESSAGE,

                TYPE_MAX = 254,
                TYPE_RESERVED = 255,
            };
            enum VERSION_MAJOR {
                VERSION_MAJOR_1 = 1,

                VERSION_MAJOR_LATEST = VERSION_MAJOR_1,
            };
            enum VERSION_MINOR {
                VERSION_MINOR_1 = 0,

                VERSION_MINOR_LATEST = VERSION_MINOR_1,
            };
            enum VERSION_PATCH {
                VERSION_PATCH_1 = 0,

                VERSION_PATCH_LATEST = VERSION_PATCH_1,
            };
            Header(uint8 type = TYPE_UNKNOWN) : _major(VERSION_MAJOR_LATEST), _minor(VERSION_MINOR_LATEST), _patch(VERSION_PATCH_LATEST), _type(type) {}
            uint8 _major;
            uint8 _minor;
            uint8 _patch;
            uint8 _type;
        };
#pragma pack()
        struct DataTextMessage {
            DataTextMessage() : _length(0) {}
            uint32 _length; //  include end of string.
            B1String _message;
        };
    };
}   //  !BnD

#endif  // !_D1NETWORK_BASE_PROTOCOL_H
