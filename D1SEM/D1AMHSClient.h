//
// D1AMHSClient.h
//
// Library: D1SEM
// Package: AMHS
// Module:  D1SEM
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1SEM_AMHS_CLIENT_H
#define _D1SEM_AMHS_CLIENT_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <B1GEM/B1GEMClient.h>

namespace BnD {
    class D1AMHSClient : public B1GEMClient {
    public:
        D1AMHSClient();
        virtual ~D1AMHSClient();
    public:
        bool requestOnline(uint16 deviceID);
    };
}   //  !BnD

#endif  // !_D1SEM_AMHS_CLIENT_H
