//
// D1StringArrayObject.cpp
//
// Library: D1Data
// Package: D1Data
// Module:  D1Data
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Data.h"
#include "D1StringArrayObject.h"

using namespace BnD;

D1StringArrayObject::D1StringArrayObject()
    : B1Object()
{
}

D1StringArrayObject::~D1StringArrayObject()
{
}

void D1StringArrayObject::archiveTo(B1Archive* archive) const
{
    writeDataToArchive("", _values, archive);
}

void D1StringArrayObject::unarchiveFrom(const B1Archive& archive)
{
    readDataFromArchive("", archive, &_values);
}
