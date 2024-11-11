//
// D1LogFileManager.h
//
// Library: D1Data
// Package: D1Data
// Module:  D1Data
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1DATA_LOG_FILE_MANAGER_H
#define _D1DATA_LOG_FILE_MANAGER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

namespace BnD {
    class D1LogFileManager {
    public:
        D1LogFileManager(B1String&& logFileExtension, B1String&& logFileDirectory);
        virtual ~D1LogFileManager();
    protected:
        enum CONSTS {
            CONSTS_LOG_FILE_LIST_BUNCH_SIZE = 100,
        };
    protected:
        const B1String _logFileExtension;
        const B1String _logFileDirectory;
    protected:
        B1String logFilePath(const B1String& fileName) const;
    public:
        std::vector<std::vector<B1String> > getLogFileList() const; //  return: vector<vector<file_list> >
        bool getCompressedLogFile(const B1String& fileName, std::vector<uint8>* data, B1String* fileChecksum) const;
        bool getCompressedLogFile(const B1String& fileName, const B1String& filePath, B1String* fileChecksum) const;
    };
}   //  !BnD

#endif  // !_D1DATA_LOG_FILE_MANAGER_H
