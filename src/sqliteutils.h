#ifndef SQLITE_UTILS_H
#define SQLITE_UTILS_H
#include <Qsql>
#include <QsqlDatabase>
#include <string>
#include "sqlite3.h"

/***********************************************************************
    Class: SQLiteDBHandle

    Author: Phil Grohe

    Wrapper class for sqlite3. Object lifecycle manages db resource.
    Opened on construction, closed on destruction.  
***********************************************************************/

class SQLiteDBHandle
{
    public:
        explicit SQLiteDBHandle(std::string filename, int flags=SQLITE_OPEN_READWRITE);
        ~SQLiteDBHandle();
        sqlite3 *get();
    private:
        SQLiteDBHandle(const SQLiteDBHandle &);
        SQLiteDBHandle &operator=(const SQLiteDBHandle &);
        sqlite3 *db;
    
};


/***********************************************************************
    Class: SQLiteStatementHandle

    Author:Phil Grohe

    Wrapper class for SQLite prepared statement. Prepares statement upon
    object construction, finalizes statement when object goes out of
    scope and is destroyed.  RAII helper class.
***********************************************************************/

class SQLiteStatementHandle
{

    public:
        SQLiteStatementHandle(std::string sql, sqlite3* db);
        ~SQLiteStatementHandle();
        sqlite3_stmt *get();

    private:
        SQLiteStatementHandle(const SQLiteStatementHandle &);
        SQLiteStatementHandle &operator=(const SQLiteStatementHandle &);
        sqlite3_stmt *compiledStatement;

};

#endif
