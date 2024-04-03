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
    class B1MariaDBConnectionPool;
    class D1MariaDBClient : protected B1MariaDBClient {
    public:
        D1MariaDBClient();
        virtual ~D1MariaDBClient();
    protected:
        struct ConnectionHandler {
            ConnectionHandler(const D1MariaDBClient* owner) : _owner(owner) { _handle = _owner->getHandle(); }
            ~ConnectionHandler() { if (_handle) _owner->releaseHandle(_handle); }
        private:
            const D1MariaDBClient* _owner;
            std::shared_ptr<B1MariaDBHandle> _handle;
        public:
            bool isValid() const { return _handle != NULL; }
            B1MariaDBHandle* handle() const { return _handle.get(); }
        }; 
    private:
        std::shared_ptr<B1MariaDBConnectionPool> _pool;
    private:
        auto getHandle() const -> std::shared_ptr<B1MariaDBHandle>;
        void releaseHandle(std::shared_ptr<B1MariaDBHandle> handle) const;
    public:
        bool initialize(B1String&& address, uint16 port, B1String&& dbName, B1String&& user, B1String&& password, uint32 connectionCount, bool useSSL = false);
        void finalize();
        void checkConnections();
        bool execute(const B1String& sql, B1MariaDBResult* result = NULL) const;
        bool executeBatch(const B1String& sql, B1MariaDBResult* result = NULL) const;
    };
}   //  !BnD

#endif  // !_D1DBCLIENT_MARIA_DB_CLIENTH_H
