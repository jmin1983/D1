//
// D1MariaDBResult.cpp
//
// Library: D1DBClient
// Package: D1DBClient
// Module:  D1DBClient
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1DBClient.h"
#include "D1MariaDBResult.h"

using namespace BnD;

D1MariaDBResult::D1MariaDBResult(B1String&& sql)
    : _sql(std::move(sql))
{
}
