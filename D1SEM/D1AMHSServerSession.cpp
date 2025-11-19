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

#include <B1SECS2/B1SECS2DataManager.h>
#include <B1SECS2/B1SECS2DataTypes.h>

using namespace BnD;

D1AMHSServerSession::D1AMHSServerSession(B1ServerSocket* serverSocket, B1BaseServerSessionListener* listener, uint16 secs2SessionID, B1GEMServer* owner)
    : B1GEMServerSession(serverSocket, listener, secs2SessionID, owner)
{
}
