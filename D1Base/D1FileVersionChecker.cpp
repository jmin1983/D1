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

#include <fstream>

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

auto D1FileVersionChecker::getFileBinaryInfo(const B1String& filePath) -> BinaryInfo
{
    BinaryInfo info;
    std::ifstream file(filePath.cString(), std::ios::binary);
    if (file.is_open() != true) {
        return info;
    }

    uint8_t magic[4] = {0};
    file.read(reinterpret_cast<char*>(magic), 4);
    if (file.gcount() < 4) {
        return info;
    }

    // linux ELF parsing.
    if (magic[0] == 0x7F && magic[1] == 'E' && magic[2] == 'L' && magic[3] == 'F') {
        info._os = OS::LINUX;
        file.seekg(0x12, std::ios::beg);
        uint16_t e_machine = 0;
        file.read(reinterpret_cast<char*>(&e_machine), 2);

        switch (e_machine) {
            case 0x0003: info._arch = ARCH::X86; break;
            case 0x003E: info._arch = ARCH::X64; break;
            case 0x0028: info._arch = ARCH::ARM32; break;
            case 0x00B7: info._arch = ARCH::ARM64; break;
            default: break;
        }
    }
    // Windows PE parsing.
    else if (magic[0] == 'M' && magic[1] == 'Z') {
        info._os = OS::WINDOWS;
        file.seekg(0x3C, std::ios::beg);
        uint32_t e_lfanew = 0;
        file.read(reinterpret_cast<char*>(&e_lfanew), 4);

        file.seekg(e_lfanew + 4, std::ios::beg);
        uint16_t machine = 0;
        file.read(reinterpret_cast<char*>(&machine), 2);

        switch (machine) {
            case 0x014C: info._arch = ARCH::X86; break;
            case 0x8664: info._arch = ARCH::X64; break;
            case 0x01C0: info._arch = ARCH::ARM32; break;
            case 0xAA64: info._arch = ARCH::ARM64; break;
            default: break;
        }
    }
    return info;
}

bool D1FileVersionChecker::isSafeToExecuteOnSystem(const B1String& filePath)
{
    const OS systemOS = B1SystemUtil::isSystemWindows() ? OS::WINDOWS :
                        B1SystemUtil::isSystemLinux() ? OS::LINUX : OS::UNKNOWN;
    const ARCH systemArch = B1SystemUtil::isSystemX64() ? ARCH::X64 :
                            B1SystemUtil::isSystemX86() ? ARCH::X86 :
                            B1SystemUtil::isSystemARM32() ? ARCH::ARM32 :
                            B1SystemUtil::isSystemARM64() ? ARCH::ARM64 : ARCH::UNKNOWN;

    if (systemOS == OS::UNKNOWN || systemArch == ARCH::UNKNOWN) {
        b1log("isSafeToExecuteOnSystem return fail unknown system os or architecture: systemOS[%d], systemArch[%d]", systemOS, systemArch);
        return false;
    }
    BinaryInfo target = getFileBinaryInfo(filePath);
    if (target._os == OS::UNKNOWN || target._arch == ARCH::UNKNOWN) {
        b1log("isSafeToExecuteOnSystem return fail unknown target file os or architecture: targetOS[%d], targetArch[%d]", target._os, target._arch);
        return false;
    }

    if (systemOS != target._os) {
        b1log("isSafeToExecuteOnSystem return fail differernt os: systemOS[%d], systemArch[%d], targetOS[%d], targetArch[%d]",
            systemOS, systemArch, target._os, target._arch);
        return false;
    }

    if (systemArch == target._arch) {
        return true;
    }
    if (systemOS == OS::WINDOWS && systemArch == ARCH::X64 && target._arch == ARCH::X86) {
        return true;
    }

    b1log("isSafeToExecuteOnSystem return fail: systemOS[%d], systemArch[%d], targetOS[%d], targetArch[%d]",
        systemOS, systemArch, target._os, target._arch);
    return false;
}
