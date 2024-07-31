//
// D1BaseServerHandleManager.cpp
//
// Library: D1Network
// Package: D1Network
// Module:  D1Network
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Network.h"
#include "D1BaseServerHandleManager.h"

using namespace BnD;

D1BaseServerHandleManager::D1BaseServerHandleManager()
{
}

D1BaseServerHandleManager::~D1BaseServerHandleManager()
{
}

bool D1BaseServerHandleManager::containsID(int32 id) const
{
    B1AutoLock al(_idHandleMapLock);
    return _idHandleMap.find(id) != _idHandleMap.end();
}

bool D1BaseServerHandleManager::addID(int32 id, int32 serverHandleID)
{
    B1AutoLock al(_idHandleMapLock);
    if (_idHandleMap.find(id) != _idHandleMap.end()) {
        B1LOG("handle already added: id[%d]", id);
        return false;
    }
    _idHandleMap.insert(std::make_pair(id, serverHandleID));
    return true;
}

void D1BaseServerHandleManager::removeID(int32 id)
{
    {
        B1AutoLock al(_idHandleMapLock);
        auto itr = _idHandleMap.find(id);
        if (itr != _idHandleMap.end()) {
            _idHandleMap.erase(itr);
            return;
        }
    }
    assert(false);
    B1LOG("unexceptionalError occurred on removeID: id[%d]", id);
}

int32 D1BaseServerHandleManager::getServerHandleID(int32 id) const
{
    B1AutoLock al(_idHandleMapLock);
    auto itr = _idHandleMap.find(id);
    if (itr == _idHandleMap.end()) {
        return -1;
    }
    return itr->second;
}
