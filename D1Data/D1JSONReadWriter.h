//
// D1JSONReadWriter.h
//
// Library: D1Data
// Package: D1Data
// Module:  D1Data
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1DATA_PROPERTY_TREE_H
#define _D1DATA_PROPERTY_TREE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <boost/property_tree/ptree.hpp>

namespace BnD {
    class D1JSONReadWriter {
    public:
        D1JSONReadWriter();
        virtual ~D1JSONReadWriter();
    protected:
        boost::property_tree::ptree _pt;
    public:
        bool readJSON(const B1String& filePath);
        bool writeJSON(const B1String& filePath);
        template<class T>
        bool get(const B1String& path, T* value) const
        {
            try { *value = _pt.get<T>(path.to_string()); }
            catch (...) { return false; }
            return true;
        }
        template<class T>
        bool put(const B1String& path, const T& value)
        {
            try { _pt.put(path.to_string(), value); }
            catch (...) { return false; }
            return true;
        }
    };
}   //  !BnD

#endif  // !_D1DATA_PROPERTY_TREE_H
