//
// D1SMSProtocol.h
//
// Library: D1Service
// Package: SMS
// Module:  D1Service
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1SERVICE_SMS_PROTOCOL_H
#define _D1SERVICE_SMS_PROTOCOL_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Network/D1BaseProtocol.h>

namespace BnD {
    namespace D1SMSProtocol {
        enum TYPE {
            TYPE_OPERATION_NTF = D1BaseProtocol::Header::TYPE_BEGIN_USER,
            TYPE_HOST_ADDRESSES_REQ,
            TYPE_HOST_ADDRESSES_RSP,
            TYPE_HOST_NAME_REQ,
            TYPE_HOST_NAME_RSP,
            TYPE_SYSTEM_RESOURCE_USAGES_REQ,
            TYPE_SYSTEM_RESOURCE_USAGES_RSP,
            TYPE_START_SYSTEM_SERVICE_REQ,
            TYPE_START_SYSTEM_SERVICE_RSP,
            TYPE_STOP_SYSTEM_SERVICE_REQ,
            TYPE_STOP_SYSTEM_SERVICE_RSP,
            TYPE_STATUS_SYSTEM_SERVICE_REQ,
            TYPE_STATUS_SYSTEM_SERVICE_RSP,

            TYPE_MAX = D1BaseProtocol::Header::TYPE_MAX,
            TYPE_RESERVED = D1BaseProtocol::Header::TYPE_RESERVED,
        };
        enum OPERATION {
            OPERATION_UNKNOWN = -1,

            OPERATION_DROP_CACHE_MEMORY = 0,
            OPERATION_REBOOT_SYSTEM,
        };
    }
}   //  !BnD

#endif  // !_D1SERVICE_SMS_PROTOCOL_H
