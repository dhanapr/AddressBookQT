#include "sqliteutils.h"
#include "sqlite3.h"

#include <string>
#include <stdexcept>
#include <iostream>

SQLiteDBHandle::SQLiteDBHandle(std::string filename, int flags)
{
     int openResult = sqlite3_open_v2(filename.c_str(),
                                    &db,
                                    flags,
                                    0);

    if(openResult != SQLITE_OK)
    {
        std::string errMsg = sqlite3_errmsg(db);
        throw std::runtime_error(errMsg);
    }        
}

SQLiteDBHandle::~SQLiteDBHandle()
{
    sqlite3_close(db);
}

sqlite3 *SQLiteDBHandle::get()
{
    return db;
}


SQLiteStatementHandle::SQLiteStatementHandle(std::string sql, sqlite3 *db)
{

    int result = sqlite3_prepare_v2(db, sql.c_str(), -1,
                                    &compiledStatement, NULL);
    if(result != SQLITE_OK)
    {
        //destroy compiled statement
        std::string errMsg = sqlite3_errmsg(db);
        sqlite3_finalize(compiledStatement);
        
        throw std::runtime_error(errMsg);
    }

}


SQLiteStatementHandle::~SQLiteStatementHandle()
{
    sqlite3_finalize(compiledStatement);
}

sqlite3_stmt *SQLiteStatementHandle::get()
{
    return compiledStatement;
}



