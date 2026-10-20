//
// D1AMHSServerSession.cpp
//
// Library: D1SEM
// Package: AMHS
// Module:  D1SEM
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1SEM.h"
#include "D1AMHSServerSession.h"
#include "D1AMHSDataManager.h"
#include "D1AMHSServer.h"

#include <B1SECS2/B1SECS2DataManager.h>
#include <B1SECS2/B1SECS2DataTypes.h>

using namespace BnD;

D1AMHSServerSession::D1AMHSServerSession(B1ServerSocket* serverSocket, B1BaseServerSessionListener* listener, uint16 secs2SessionID, D1AMHSServer* owner,
                                         uint32 timeoutT3, uint32 timeoutT6, uint32 timeoutT7, uint32 timeoutT8, uint32 timeoutLinkTest)
    : B1GEMServerSession(serverSocket, listener, secs2SessionID, owner, timeoutT3, timeoutT6, timeoutT7, timeoutT8, timeoutLinkTest)
{
}

D1AMHSServer* D1AMHSServerSession::owner() const
{
    return static_cast<D1AMHSServer*>(B1GEMServerSession::owner());
}

auto D1AMHSServerSession::serverAmhsDataManager() const -> const D1AMHSDataManager*
{
    return owner()->serverAmhsDataManager();
}
