//
// D1EntityState.h
//
// Library: D1EQData
// Package: D1EQData
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1EQDATA_ENTITY_STATE_H
#define _D1EQDATA_ENTITY_STATE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Data/D1RedisHashmapObject.h>
#include <D1EQData/D1NotifiableObject.h>

namespace BnD {
    class D1RedisClientInterface;
    class D1EntityState : public D1NotifiableObject
                        , public D1RedisHashmapObject {
    public:
        D1EntityState();
        D1EntityState(B1String&& name);
        virtual ~D1EntityState();
    protected:
        DataString _name;
    protected:
        virtual void archiveTo(B1Archive* archive) const override;
        virtual void unarchiveFrom(const B1Archive& archive) override;
    protected:
        virtual B1String redisKey() const override;
        virtual bool isValidToMakeRedisString() const override { return true; }
        virtual void makeRedisStringArgs(std::vector<B1String>* args) const override;
        virtual bool readRedisMap(const std::map<B1String, B1String>& map) override;
    public:
        D1EntityState& operator=(const D1EntityState& d)
        {
            _name.second = d._name.second.copy();
            return *this;
        }
        bool operator==(const D1EntityState& d) const
        {
            return _name.second == d._name.second;
        }
        bool operator!=(const D1EntityState& d) const { return operator==(d) != true; }
    public:
        const B1String& name() const { return _name.second; }
        void setName(B1String&& value) { _name.second = std::move(value); }
        void reloadStates(D1RedisClientInterface* redisReader);
        void notifyAttributesChanged(D1RedisClientInterface* delayedCommander, bool isEssential = false) const;
    };
}

#endif  // !_D1EQDATA_ENTITY_STATE_H
