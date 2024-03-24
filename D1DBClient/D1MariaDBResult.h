//
// D1MariaDBResult.h
//
// Library: D1DBClient
// Package: D1DBClient
// Module:  D1DBClient
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1DBCLIENT_MARIA_DB_RESULT_H
#define _D1DBCLIENT_MARIA_DB_RESULT_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif
 
#include <B1DBClient/B1MariaDBResult.h>

namespace BnD {
    class D1MariaDBResult : public B1MariaDBResult {
    public:
        D1MariaDBResult(B1String&& sql);
    protected:
        const B1String _sql;
    public:
        const B1String& sql() const { return _sql; }
    };

    template<typename T>
    class MariaDBDataTypeResult : public D1MariaDBResult {
    public:
        MariaDBDataTypeResult(T* data, B1String&& sql) : D1MariaDBResult(std::move(sql)), _data(data) {}
    private:
        T* _data;
    protected:
        virtual bool implReadDBResult(const boost::mysql::rows_view& rows, T* data) = 0;
    protected:
        bool implReadDBResult(const boost::mysql::rows_view& rows) final
        {
            return implReadDBResult(rows, _data);
        }
    };
}   //  !BnD

#endif  // !_D1DBCLIENT_MARIA_DB_RESULT_H
