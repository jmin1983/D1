//
// D1RawFileReader.h
//
// Library: D1Data
// Package: D1Data
// Module:  D1Data
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1DATA_RAW_FILE_READER_H
#define _D1DATA_RAW_FILE_READER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

namespace BnD {
    class D1JSONReadWriter;
    class D1RawFileReader {
    public:
        D1RawFileReader();
        virtual ~D1RawFileReader();
    private:
        std::shared_ptr<D1JSONReadWriter> _jsonReadWriter;
    protected:
        virtual B1String implToString() const { return ""; }
        virtual bool implLoad(const B1String& filePath);
        virtual bool implSave(const B1String& filePath);
        virtual bool validate() const { return true; }
        virtual bool readData() = 0;
        virtual bool writeData() = 0;
    protected:
        bool readJSON(const B1String& filePath);
        bool writeJSON(const B1String& filePath);
        bool getBool(const B1String& path, bool* value) const;
        bool getInt32(const B1String& path, int32* value) const;
        bool getString(const B1String& path, B1String* value) const;
        bool putBool(const B1String& path, bool value);
        bool putInt32(const B1String& path, int32 value);
        bool putString(const B1String& path, const B1String& value);
    public:
        B1String toString() const;
        bool load(const B1String& filePath);
        bool save(const B1String& filePath);
    };
}   //  !BnD

#endif  // !_D1DATA_RAW_FILE_READER_H
