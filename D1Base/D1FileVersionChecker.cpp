//
// D1FileVersionChecker.cpp
//
// Library: D1Base
// Package: D1Base
// Module:  D1Base
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Base.h"
#include "D1FileVersionChecker.h"

#include <B1Base/B1Endian.h>
#include <B1Base/B1SystemUtil.h>
#include <B1Base/B1Thread.h>
#include <B1Util/B1FileUtil.h>

using namespace BnD;

bool D1FileVersionChecker::readVersionFile(const B1String& versionFilePath, int32* version, B1String* identifier, B1String* buildDate)
{
    auto data = B1FileUtil::readFile(versionFilePath);
    int32 versionData = 0;
    int32 identifierLengthData = 0;
    int32 buildDateLengthData = 0;
    if (data.size() < sizeof(versionData) + sizeof(identifierLengthData) + sizeof(buildDateLengthData)) {
        return false;
    }

    memcpy(&versionData, &data[0], sizeof(versionData));
    if (version) {
        *version = TO_INT32_FOR_NETWORK(versionData);
    }
    memcpy(&identifierLengthData, &data[sizeof(versionData)], sizeof(identifierLengthData));
    int32 identifierLength = TO_INT32_FOR_NETWORK(identifierLengthData);
    if (data.size() < sizeof(versionData) + sizeof(identifierLengthData) + sizeof(buildDateLengthData) + identifierLength) {
        return false;
    }
    if (identifier) {
        std::vector<char> temp(data.begin() + sizeof(versionData) + sizeof(identifierLengthData), data.end());
        temp.push_back(0);
        identifier->from(&temp[0]);
    }
    memcpy(&buildDateLengthData, &data[sizeof(versionData) + sizeof(identifierLengthData) + identifierLength], sizeof(buildDateLengthData));
    int32 buildDateLength = TO_INT32_FOR_NETWORK(buildDateLengthData);
    if (data.size() < sizeof(versionData) + sizeof(identifierLengthData) + sizeof(buildDateLengthData) + identifierLength + buildDateLength) {
        return false;
    }
    if (buildDate) {
        std::vector<char> temp(data.begin() + sizeof(versionData) + sizeof(identifierLengthData) + identifierLength + sizeof(buildDateLengthData), data.end());
        temp.push_back(0);
        buildDate->from(&temp[0]);
    }
    return true;
}

bool D1FileVersionChecker::writeVersionFile(int32 version, const B1String& identifier, const B1String& buildDate, const B1String& versionFilePath)
{
    std::vector<uint8> data;
    int32 versionData = TO_INT32_FOR_NETWORK(version);
    int32 identifierLengthData = TO_INT32_FOR_NETWORK(identifier.length());
    int32 buildDateLengthData = TO_INT32_FOR_NETWORK(buildDate.length());
    data.insert(data.end(), (uint8*)&versionData, (uint8*)&versionData + sizeof(versionData));
    data.insert(data.end(), (uint8*)&identifierLengthData, (uint8*)&identifierLengthData + sizeof(identifierLengthData));
    data.insert(data.end(), identifier.cString(), identifier.cString() + identifier.length());
    data.insert(data.end(), (uint8*)&buildDateLengthData, (uint8*)&buildDateLengthData + sizeof(buildDateLengthData));
    data.insert(data.end(), buildDate.cString(), buildDate.cString() + buildDate.length());
    return B1FileUtil::writeFile(data, versionFilePath);
}

bool D1FileVersionChecker::getFileVersion(const B1String& filePath, int32* version, B1String* identifier, B1String* buildDate)
{
    std::vector<B1String> args(2);
    args[0] = "VERSION";
    args[1] = "version";
    if (B1SystemUtil::createProcessArgs(filePath, args) != 0) {
        return false;
    }
    const B1String versionFilePath = filePath + "." + args[1];
    bool fileGenerated = false;
    for (int32 i = 0; i < 10; ++i) {
        if (B1SystemUtil::isFileExist(versionFilePath)) {
            fileGenerated = true;
            break;
        }
        B1Thread::sleep(100);
    }
    if (fileGenerated != true) {
        return false;
    }
    bool result = readVersionFile(versionFilePath, version, identifier, buildDate);
    B1SystemUtil::deleteFile(versionFilePath);
    return result;
}
