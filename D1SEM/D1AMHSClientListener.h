//
// D1AMHSClientListener.h
//
// Library: D1SEM
// Package: AMHS
// Module:  D1SEM
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1SEM_AMHS_CLIENT_LISTENER_H
#define _D1SEM_AMHS_CLIENT_LISTENER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

namespace BnD {
    class D1AMHSClientListener {
    public:
        virtual void onConnect(uint16 deviceID) {}
        virtual void onDisconnected(uint16 deviceID, int32 reason) {}
        virtual void onSelectCompleted(uint16 deviceID) {}
        virtual void onRequestOnlineCompleted(uint16 deviceID) {}
        virtual void onRequestOnlineFailed(uint16 deviceID) {}      //  can not communication now.
        virtual void onRequestOnlineRejected(uint16 deviceID) {}    //  rejected online(ONLACK failed) for now. eq will send S1F1 later.
    };
}   //  !BnD

#endif  // !_D1SEM_AMHS_CLIENT_LISTENER_H
