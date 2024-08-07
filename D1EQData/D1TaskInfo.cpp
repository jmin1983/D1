//
// D1TaskInfo.cpp
//
// Library: D1EQData
// Package: Task
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1EQData.h"
#include "D1TaskInfo.h"

#include <D1Base/D1Consts.h>

using namespace BnD;

const B1String D1TaskInfo::_taskInfoKey("TaskInfo");

D1TaskInfo::D1TaskInfo()
    : D1NotifiableObject()
    , D1RedisHashmapObject()
    , _taskID("TaskID", D1Consts::ID_INVALID)
{
}

D1TaskInfo::D1TaskInfo(int64 taskID)
    : D1NotifiableObject()
    , D1RedisHashmapObject()
    , _taskID("TaskID", taskID)
{
}

D1TaskInfo::~D1TaskInfo()
{
}

void D1TaskInfo::archiveTo(B1Archive* archive) const
{
    writeDataToArchive(_taskID, archive);
}

void D1TaskInfo::unarchiveFrom(const B1Archive& archive)
{
    readDataFromArchive(archive, &_taskID);
}

B1String D1TaskInfo::redisKey() const
{
    return redisKey(taskID());
}

bool D1TaskInfo::readBulkRedisMap(const std::map<B1String, B1String>& map)
{
    return readRedisMap(map);
}

bool D1TaskInfo::isValidToMakeRedisString() const
{
    return taskID() != D1Consts::ID_INVALID;
}

B1String D1TaskInfo::redisKey(int64 taskID)
{
    assert(taskID != D1Consts::ID_INVALID);
    return taskID != D1Consts::ID_INVALID ? B1String::formatAs("%s:%lld", _taskInfoKey.cString(), taskID) : "";
}
