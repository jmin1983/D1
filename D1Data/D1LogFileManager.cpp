//
// D1LogFileManager.cpp
//
// Library: D1Data
// Package: D1Data
// Module:  D1Data
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Data.h"
#include "D1LogFileManager.h"

#include <B1Base/B1SystemUtil.h>
#include <B1Crypto/B1MD5.h>
#include <B1Util/B1Compressor.h>
#include <B1Util/B1FileUtil.h>

using namespace BnD;

D1LogFileManager::D1LogFileManager(B1String&& logFileExtension, B1String&& logFileDirectory)
    : _logFileExtension(std::move(logFileExtension))
    , _logFileDirectory(std::move(logFileDirectory))
{
}

D1LogFileManager::~D1LogFileManager()
{
}

B1String D1LogFileManager::logFilePath(const B1String& fileName) const
{
    return _logFileDirectory + "/" + fileName;
}

auto D1LogFileManager::getLogFileList() const -> std::vector<std::vector<B1String> >
{
    std::list<B1String> files;
    B1SystemUtil::findFiles(_logFileDirectory, _logFileExtension, &files);
    if (files.empty()) {
        return std::vector<std::vector<B1String> >();
    }
    if (files.size() <= CONSTS_LOG_FILE_LIST_BUNCH_SIZE) {
        std::vector<B1String> temp(std::make_move_iterator(files.begin()), std::make_move_iterator(files.end()));
        std::vector<std::vector<B1String> > result;
        result.push_back(std::move(temp));
        return result;
    }

    const size_t size = files.size() / CONSTS_LOG_FILE_LIST_BUNCH_SIZE + 1;
    std::vector<std::vector<B1String> > result;
    result.resize(size);
    for (auto& r : result) {
        r.reserve(CONSTS_LOG_FILE_LIST_BUNCH_SIZE);
    }
    size_t index = 0;
    for (auto& file : files) {
        result[index / CONSTS_LOG_FILE_LIST_BUNCH_SIZE].push_back(std::move(file));
        index++;
    }
    return result;
}

bool D1LogFileManager::getCompressedLogFile(const B1String& fileName, std::vector<uint8>* data, B1String* fileChecksum) const
{
    auto fileData = B1FileUtil::readFile(logFilePath(fileName));
    if (fileData.empty()) {
        return false;
    }
    *fileChecksum = B1MD5::getFileMD5(fileData);
    *data = B1Compressor::compress(fileData);
    return data->empty() != true;
}

bool D1LogFileManager::getCompressedLogFile(const B1String& fileName, const B1String& filePath, B1String* fileChecksum) const
{
    auto fileData = B1FileUtil::readFile(logFilePath(fileName));
    if (fileData.empty()) {
        return false;
    }
    *fileChecksum = B1MD5::getFileMD5(fileData);
    return B1Compressor::compressToFile(fileData, filePath);
}
