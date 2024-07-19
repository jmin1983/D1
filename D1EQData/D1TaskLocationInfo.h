//
// D1TaskLocationInfo.h
//
// Library: D1EQData
// Package: Task
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1EQDATA_TASK_LOCATION_INFO_H
#define _D1EQDATA_TASK_LOCATION_INFO_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1EQData/D1TaskInfo.h>

namespace BnD {
    class D1RedisClientInterface;
    class D1TaskLocationInfo : public D1TaskInfo {
    public:
        D1TaskLocationInfo();
        D1TaskLocationInfo(int32 taskID);
        D1TaskLocationInfo(int32 taskID, int32 currentLocation);
        virtual ~D1TaskLocationInfo();
    protected:
        DataInt32 _currentLocation;
    protected:
        virtual void archiveTo(B1Archive* archive) const override;
        virtual void unarchiveFrom(const B1Archive& archive) override;
        virtual D1MessageObject* createMessageObject() const override;
    protected:
        virtual bool isValidToMakeRedisString() const override;
        virtual void makeRedisStringArgs(std::vector<B1String>* args) const override;
        virtual bool readRedisMap(const std::map<B1String, B1String>& map) override;
    public:
        int32 currentLocation() const { return _currentLocation.second; }
        void setCurrentLocation(int32 location) { _currentLocation.second = location; }
    };
}   //  !BnD

#endif  // !_D1EQDATA_TASK_LOCATION_INFO_H
