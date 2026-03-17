//
// D1Unit.h
//
// Library: D1EQData
// Package: Unit
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1EQDATA_D1UNIT_H
#define _D1EQDATA_D1UNIT_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <B1Base/B1Object.h>

#include <D1Data/D1RedisHashmapObject.h>

namespace BnD {
    class D1UnitStateAttributes;
    class D1Unit : public B1Object
                 , public D1RedisHashmapObject {
    public:
        D1Unit();
        D1Unit(int32 unitID);
        virtual ~D1Unit() {}
    public:
        enum UNIT_TYPE_ID_RANGE {
            UNIT_TYPE_ID_RANGE_INVALID = -1,

            UNIT_TYPE_ID_RANGE_BEGIN = 0,

            UNIT_TYPE_ID_RANGE_SERVICE_SET_MIN = UNIT_TYPE_ID_RANGE_BEGIN + 1,
            UNIT_TYPE_ID_RANGE_SERVICE_SET_MAX = UNIT_TYPE_ID_RANGE_SERVICE_SET_MIN + 1999,

            UNIT_TYPE_ID_RANGE_NVR_MIN = UNIT_TYPE_ID_RANGE_SERVICE_SET_MAX,
            UNIT_TYPE_ID_RANGE_NVR_MAX = UNIT_TYPE_ID_RANGE_NVR_MIN + 999,

            UNIT_TYPE_ID_RANGE_END = UNIT_TYPE_ID_RANGE_NVR_MAX,
        };
    private:
        DataInt32 _unitID;
        DataString _name;
        DataString _user;
        DataString _password;
        DataString _serverAddress;
        DataUint16 _serverPort;
    protected:
        std::shared_ptr<D1UnitStateAttributes> _stateAttributes;
    protected:
        virtual void implInitializeAttributes(D1RedisClientInterface* redisReader);
        virtual void archiveToWithoutAttributes(B1Archive* archive) const;
    protected:
        virtual void archiveTo(B1Archive* archive) const override;
        virtual void unarchiveFrom(const B1Archive& archive) override;
    protected:
        virtual void makeRedisStringArgs(std::vector<B1String>* args) const override;
        virtual bool readRedisMap(const std::map<B1String, B1String>& map) override;
    public:
        void initializeAttributes(D1RedisClientInterface* redisReader);
        int32 unitID() const { return _unitID.second; }
        const B1String& name() const { return _name.second; }
        const B1String& user() const { return _user.second; }
        const B1String& password() const { return _password.second; }
        const B1String& serverAddress() const { return _serverAddress.second; }
        uint16 serverPort() const { return _serverPort.second; }

        bool isAlarmed() const;
        bool isInService() const;
        bool isOutOfService() const;
        bool isOffLine() const;
        bool isUnitTypeServiceSet() const;
        bool isUnitTypeNVR() const;

        D1UnitStateAttributes* stateAttributes() const { return _stateAttributes.get(); }

        bool archiveToStringWithoutAttributes(B1String* result, bool pretty = false) const;
    };
    typedef std::shared_ptr<D1Unit> SPD1Unit;
}

#endif  // !_D1EQDATA_D1UNIT_H
