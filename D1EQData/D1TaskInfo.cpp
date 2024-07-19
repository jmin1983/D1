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

D1TaskInfo::D1TaskInfo()
    : D1NotifiableObject()
    , D1RedisHashmapObject()
    , _taskID("TaskID", D1Consts::ID_INVALID)
{
}

D1TaskInfo::D1TaskInfo(int32 taskID)
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
    assert(taskID() != D1Consts::ID_INVALID);
    return taskID() != D1Consts::ID_INVALID ? B1String::formatAs("TaskInfo:%d", taskID()) : "";
}

bool D1TaskInfo::isValidToMakeRedisString() const
{
    return taskID() != D1Consts::ID_INVALID;
}
