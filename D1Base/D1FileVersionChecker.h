//
// D1FileVersionChecker.h
//
// Library: D1Base
// Package: D1Base
// Module:  D1Base
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1BASE_FILE_VERSION_CHECKER_H
#define _D1BASE_FILE_VERSION_CHECKER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

namespace BnD {
    namespace D1FileVersionChecker {
        enum class OS {
            UNKNOWN = -1,

            WINDOWS,
            LINUX,
        };
        enum class ARCH {
            UNKNOWN = -1,

            X86,
            X64,
            ARM32,
            ARM64,
        };
        struct BinaryInfo {
            OS _os = OS::UNKNOWN;
            ARCH _arch = ARCH::UNKNOWN;
        };
        bool readVersionFile(const B1String& versionFilePath, int32* version, B1String* identifier, B1String* buildDate);
        bool writeVersionFile(int32 version, const B1String& identifier, const B1String& buildDate, const B1String& versionFilePath);
        bool getFileVersion(const B1String& filePath, int32* version, B1String* identifier, B1String* buildDate);
        BinaryInfo getFileBinaryInfo(const B1String& filePath);
        bool isSafeToExecuteOnSystem(const B1String& filePath);
    };
}   //  !BnD

#endif  // !_D1BASE_FILE_VERSION_CHECKER_H
