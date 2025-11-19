//
// D1AMHSServerSession.h
//
// Library: D1SEM
// Package: AMHS
// Module:  D1SEM
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1SEM_AMHS_SERVER_SESSION_H
#define _D1SEM_AMHS_SERVER_SESSION_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <B1GEM/B1GEMServerSession.h>

namespace BnD {
    class D1AMHSServerSession : public B1GEMServerSession {
    public:
        D1AMHSServerSession(B1ServerSocket* serverSocket, B1BaseServerSessionListener* listener, uint16 secs2SessionID, B1GEMServer* owner);
    };
}   //  !BnD

#endif  // !_D1SEM_AMHS_SERVER_SESSION_H
