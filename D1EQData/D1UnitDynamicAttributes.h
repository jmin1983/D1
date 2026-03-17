//
// D1UnitDynamicAttributes.h
//
// Library: D1EQData
// Package: Unit
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1EQDATA_UNIT_DYNAMIC_ATTRIBUTES_H
#define _D1EQDATA_UNIT_DYNAMIC_ATTRIBUTES_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Data/D1RedisHashmapObject.h>
#include <D1EQData/D1NotifiableObject.h>

namespace BnD {
    class D1RedisClientInterface;
    class D1UnitDynamicAttributes : public D1NotifiableObject
                                  , public D1RedisHashmapObject {
    public:
        D1UnitDynamicAttributes();
        D1UnitDynamicAttributes(int32 unitID);
        virtual ~D1UnitDynamicAttributes();
    protected:
        DataInt32 _unitID;
    protected:
        virtual void archiveTo(B1Archive* archive) const override;
        virtual void unarchiveFrom(const B1Archive& archive) override;
    protected:
        virtual B1String redisKey() const override;
    public:
        D1UnitDynamicAttributes& operator=(const D1UnitDynamicAttributes& d)
        {
            //  _unitID, _serviceID is immutable.
            return *this;
        }
        bool operator==(const D1UnitDynamicAttributes& d) const
        {
            return _unitID.second == d._unitID.second;
        }
        bool operator!=(const D1UnitDynamicAttributes& d) const { return operator==(d) != true; }
    public:
        int32 unitID() const { return _unitID.second; }
        void reloadStates(D1RedisClientInterface* redisReader);
        void notifyAttributesChanged(D1RedisClientInterface* delayedCommander, bool isEssential = false) const;
    };
}

#endif  // !_D1EQDATA_UNIT_DYNAMIC_ATTRIBUTES_H
