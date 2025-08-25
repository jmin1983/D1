//
// D1AppService.h
//
// Library: D1Service
// Package: D1Service
// Module:  D1Service
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1SERVICE_APP_SERVICE_H
#define _D1SERVICE_APP_SERVICE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Base/D1BaseService.h>

namespace BnD {
    class D1AppService : public D1BaseService {
    public:
        D1AppService(std::shared_ptr<D1ProductIdentifier> productIdentifier, int32 version, B1String&& buildDate, B1String&& systemName);
        virtual ~D1AppService();
    protected:
        virtual void getSMSServerInfo(B1String* smsAddress, int32* smsPort) const = 0;
    protected:
        virtual B1String getNetworkAddressesString() const;
    };
}   //  !BnD

#endif  // !_D1SERVICE_APP_SERVICE_H
