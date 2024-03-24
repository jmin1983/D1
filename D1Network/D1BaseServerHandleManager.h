//
// D1BaseServerHandleManager.h
//
// Library: D1Network
// Package: D1Network
// Module:  D1Network
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1NETWORK_BASE_SERVER_HANDLE_MANAGER_H
#define _D1NETWORK_BASE_SERVER_HANDLE_MANAGER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <B1Base/B1Lock.h>

#include <map>

namespace BnD {
    class D1BaseServerHandleManager {
    public:
        D1BaseServerHandleManager();
        virtual ~D1BaseServerHandleManager();
    protected:
        std::map<int32, int32> _idHandleMap;  //  map<id, server_handle_id>
        mutable B1Lock _idHandleMapLock;
    public:
        bool containsID(int32 id) const;
        bool addID(int32 id, int32 serverHandleID);
        void removeID(int32 id);
        int32 getServerHandleID(int32 id) const;
    };
}   //  !BnD

#endif  // !_D1NETWORK_BASE_SERVER_HANDLE_MANAGER_H
