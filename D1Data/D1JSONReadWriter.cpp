//
// D1JSONReadWriter.cpp
//
// Library: D1Data
// Package: D1Data
// Module:  D1Data
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Data.h"
#include "D1JSONReadWriter.h"

#include <boost/property_tree/json_parser.hpp>

using namespace BnD;

D1JSONReadWriter::D1JSONReadWriter()
    : _pt()
{
}

D1JSONReadWriter::~D1JSONReadWriter()
{
}

bool D1JSONReadWriter::readJSON(const B1String& filePath)
{
    try {
        boost::property_tree::read_json(filePath.to_string(), _pt);
    }
    catch (...) {
        return false;
    }
    return true;
}

bool D1JSONReadWriter::writeJSON(const B1String& filePath)
{
    try {
        boost::property_tree::write_json(filePath.to_string(), _pt);
    }
    catch (...) {
        return false;
    }
    return true;
}
