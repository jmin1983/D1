//
// D1MariaDBClient.h
//
// Library: D1DBClient
// Package: D1DBClient
// Module:  D1DBClient
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1DBCLIENT_MARIA_DB_CLIENTH_H
#define _D1DBCLIENT_MARIA_DB_CLIENTH_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <B1DBClient/B1MariaDBClient.h>

namespace BnD {
    class D1MariaDBClient : public B1MariaDBClient {
    public:
        D1MariaDBClient();
        virtual ~D1MariaDBClient();
    };
}   //  !BnD

#endif  // !_D1DBCLIENT_MARIA_DB_CLIENTH_H
