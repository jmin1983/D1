//
// D1MariaDBClient.cpp
//
// Library: D1DBClient
// Package: D1DBClient
// Module:  D1DBClient
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1DBClient.h"
#include "D1MariaDBClient.h"

#include <B1DBClient/B1MariaDBConnectionPool.h>

using namespace BnD;

D1MariaDBClient::D1MariaDBClient()
{
}

D1MariaDBClient::~D1MariaDBClient()
{
}

auto D1MariaDBClient::getHandle() const -> std::shared_ptr<B1MariaDBHandle>
{
    return _pool ? _pool->getHandle() : std::shared_ptr<B1MariaDBHandle>();
}

void D1MariaDBClient::releaseHandle(std::shared_ptr<B1MariaDBHandle> handle) const
{
    if (_pool) {
        _pool->releaseHandle(handle);
    }
}

bool D1MariaDBClient::initialize(B1String&& address, uint16 port, B1String&& dbName, B1String&& user, B1String&& password, uint32 connectionCount, bool useSSL)
{
    if (_pool) {
        return false;
    }
    _pool.reset(new B1MariaDBConnectionPool());
    if (_pool->initialize(std::move(address), port, std::move(dbName), std::move(user), std::move(password), connectionCount, useSSL) != true) {
        _pool->finalize();
        _pool.reset();
    }
    return true;
}

void D1MariaDBClient::finalize()
{
    if (_pool) {
        _pool->finalize();
        _pool.reset();
    }
}

void D1MariaDBClient::checkConnections()
{
    if (_pool) {
        _pool->checkConnections();
    }
}

bool D1MariaDBClient::execute(const B1String& sql, B1MariaDBResult* result) const
{
    ConnectionHandler handler(this);
    if (handler.isValid() != true) {
        return false;
    }
    return B1MariaDBClient::execute(handler.handle(), sql, result);
}

bool D1MariaDBClient::executeBatch(const B1String& sql, B1MariaDBResult* result) const
{
    ConnectionHandler handler(this);
    if (handler.isValid() != true) {
        return false;
    }
    return B1MariaDBClient::executeBatch(handler.handle(), sql, result);
}
