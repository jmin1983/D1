//
// D1WarningManager.h
//
// Library: D1Data
// Package: D1Data
// Module:  D1Data
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1DATA_WARNING_MANAGER_H
#define _D1DATA_WARNING_MANAGER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Data/D1EventManager.h>

namespace BnD {
    class D1WarningManager : public D1EventManager {
    public:
        D1WarningManager();
    public:
        bool addWarning(int32 code, const B1String &commandID, const B1String &carrierID, int64 taskID, int32 zoneID, int32 reason);
        bool addWarning(int32 code);
        bool addWarning(int32 code, int32 zoneID);
        bool addWarning(int32 code, int64 taskID, int32 zoneID, int32 reason);
    public:
        static D1WarningManager* getMe() { return static_cast<D1WarningManager*>(get()); }
    };
}   //  !BnD

#endif  // !_D1DATA_WARNING_MANAGER_H
