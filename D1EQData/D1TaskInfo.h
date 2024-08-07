//
// D1TaskInfo.h
//
// Library: D1EQData
// Package: Task
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1EQDATA_TASK_INFO_H
#define _D1EQDATA_TASK_INFO_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Data/D1RedisHashmapObject.h>
#include <D1EQData/D1NotifiableObject.h>

namespace BnD {
    class D1TaskInfo : public D1NotifiableObject
                     , public D1RedisHashmapObject {
    public:
        D1TaskInfo();
        D1TaskInfo(int64 taskID);
        virtual ~D1TaskInfo();
    private:
        static const B1String _taskInfoKey;
        DataInt64 _taskID;
    protected:
        virtual void archiveTo(B1Archive* archive) const override;
        virtual void unarchiveFrom(const B1Archive& archive) override;
    protected:
        virtual B1String redisKey() const override;
        virtual bool isValidToMakeRedisString() const override;
    public:
        int64 taskID() const { return _taskID.second; }
        bool readBulkRedisMap(const std::map<B1String, B1String>& map);
    public:
        static const B1String& taskInfoKey() { return _taskInfoKey; }
        static B1String redisKey(int64 taskID);
    };
    typedef std::shared_ptr<D1TaskInfo> SPD1TaskInfo;
}   //  !BnD

#endif  // !_D1EQDATA_TASK_INFO_H
