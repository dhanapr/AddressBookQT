#include "sqlitedatasource.h"

#include <algorithm>
#include <sqlite3.h>
#include <string>
#include <stdexcept>
#include <vector>
#include "addressbookview.h"
#include "contact.h"
#include "errorinfo.h"
#include "sqliteutils.h"


//Non Member Utility Functions


   
SQLiteDataSource::SQLiteDataSource(const std::string &filename, bool createDB):
                            database(filename,
                            (createDB ? (SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE) :
                            SQLITE_OPEN_READWRITE))
{
    createTable();
}   

SQLiteDataSource::~SQLiteDataSource()
{
}

void SQLiteDataSource::createTable()
{
    //Prepare the SQLite statement
    std::string sqlStr = "CREATE TABLE IF NOT EXISTS Contacts"
                        "(id INTEGER PRIMARY KEY,"
                        "firstname TEXT NOT NULL,"
                        "lastname TEXT NOT NULL,"
                        "phonenum TEXT NOT NULL,"
                        "address TEXT,"
                        "email TEXT);";

    SQLiteStatementHandle createTableStatement(sqlStr, database.get());

    //Execute the SQLite statement
    int result = sqlite3_step(createTableStatement.get());

    if(result != SQLITE_DONE)
    {
        std::string errMsg = sqlite3_errmsg(database.get());
        throw std::runtime_error(errMsg);
    }

 
}

bool SQLiteDataSource::isViewRegistered(AddressBookView *viewToCheck)
{
    std::vector<AddressBookView*>::const_iterator it;
    it = std::find(observerList.begin(), observerList.end(), viewToCheck);

    if(it == observerList.end())
    {
        return false;
    }
    else
    {
        return true;
    }
}

void SQLiteDataSource::registerView(AddressBookView *viewToRegister)
{
    
    if(viewToRegister && !isViewRegistered(viewToRegister))
    {
        observerList.push_back(viewToRegister);
    }

}

void SQLiteDataSource::removeView(AddressBookView *viewToRemove)
{
    if(viewToRemove)
    {
        //Find the view in the list and remove it
        std::vector<AddressBookView*>::iterator it;
        it = std::find(observerList.begin(), observerList.end(), viewToRemove);

        if(it != observerList.end())
            observerList.erase(it);

    }
 
}

void SQLiteDataSource::notifyViews()
{
    std::vector<AddressBookView*>::iterator it;

    for(it = observerList.begin(); it != observerList.end(); it++)
    {
        (*it)->updateView();
    }

}

void SQLiteDataSource::fillContactFromRow(sqlite3_stmt *s, Contact& c)
{
 
    c.id = sqlite3_column_int(s, 0);
    c.firstName = reinterpret_cast<const char*>(sqlite3_column_text(s, 1));
    c.lastName = reinterpret_cast<const char*>(sqlite3_column_text(s, 2));
    c.phoneNumber = reinterpret_cast<const char*>(sqlite3_column_text(s, 3));
    c.address = reinterpret_cast<const char*>(sqlite3_column_text(s, 4));
    c.email = reinterpret_cast<const char*>(sqlite3_column_text(s, 5));
}


ErrorInfo SQLiteDataSource::getContact(Contact::ContactId id, Contact& c)
{
    //create sql prepared statement
    std::string sqlStr = "SELECT * FROM Contacts WHERE id=?;"; 

    SQLiteStatementHandle queryStatement(sqlStr, database.get());

    //bind parameters to SQL statement
    sqlite3_bind_int(queryStatement.get(), 1, id);

    //execute statement & check result
    int stepResult = sqlite3_step(queryStatement.get());
    
    if(stepResult != SQLITE_ROW)
    {
        return ErrorInfo(ERR_DATASOURCE_ERROR, "Could not retrieve contact.");
    }

    //package column values into Out parameter 
    fillContactFromRow(queryStatement.get(), c);

    return ErrorInfo(ERR_OK, "OK");
}

ErrorInfo SQLiteDataSource::getAllContacts(Contact::ContactRecordSet &rs)
{
    //create sql prepared statement
    std::string sqlStr = "SELECT * FROM Contacts;"; 

    SQLiteStatementHandle queryStatement(sqlStr, database.get());


    //execute statement & check result
    int stepResult = sqlite3_step(queryStatement.get());
    
    if(stepResult != SQLITE_ROW)
    {
        return ErrorInfo(ERR_DATASOURCE_ERROR, "Could not retrieve contacts.");
    }

    Contact::ContactRecordSet rows;

    while(stepResult == SQLITE_ROW)
    {
        Contact temp;
                
        //package column values into Out parameter 
        fillContactFromRow(queryStatement.get(), temp);
        rows.push_back(temp);

        stepResult = sqlite3_step(queryStatement.get());
    }

    rs = rows;

    return ErrorInfo(ERR_OK, "OK");
}


ErrorInfo SQLiteDataSource::addContact(const Contact& c)
{
    //create sql prepared statement
    std::string sqlStr = "INSERT INTO Contacts VALUES("
                        "NULL,?,?,?,?,?);";
    
    SQLiteStatementHandle insertStatement(sqlStr, database.get()); 

    //bind contact fields to variables in SQL statement
    //id is not bound, it is an auto-incrementing key field
    sqlite3_bind_text(insertStatement.get(), 1, c.firstName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(insertStatement.get(), 2, c.lastName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(insertStatement.get(), 3, c.phoneNumber.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(insertStatement.get(), 4, c.address.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(insertStatement.get(), 5, c.email.c_str(), -1, SQLITE_STATIC);

    //execute SQL statement & check results
    int stepResult = sqlite3_step(insertStatement.get());
    
    if(stepResult != SQLITE_DONE)
    {
        return ErrorInfo(ERR_DATASOURCE_ERROR, "Could not add contact");
    }


    notifyViews();

    return ErrorInfo(ERR_OK, "OK");
}
ErrorInfo SQLiteDataSource::searchContact(const Contact& c)
{
    //create sql prepared statement
    std::string sqlStr = "INSERT INTO Contacts VALUES("
                        "NULL,?,?,?,?,?);";

    SQLiteStatementHandle insertStatement(sqlStr, database.get());

    //bind contact fields to variables in SQL statement
    //id is not bound, it is an auto-incrementing key field
    sqlite3_bind_text(insertStatement.get(), 1, c.firstName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(insertStatement.get(), 2, c.lastName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(insertStatement.get(), 3, c.phoneNumber.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(insertStatement.get(), 4, c.address.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(insertStatement.get(), 5, c.email.c_str(), -1, SQLITE_STATIC);

    //execute SQL statement & check results
    int stepResult = sqlite3_step(insertStatement.get());

    if(stepResult != SQLITE_DONE)
    {
        return ErrorInfo(ERR_DATASOURCE_ERROR, "Could not add contact");
    }


    notifyViews();

    return ErrorInfo(ERR_OK, "OK");
}

ErrorInfo SQLiteDataSource::updateContact(Contact::ContactId id, const Contact& c)
{
    //create sql prepared statement
    std::string sqlStr = "UPDATE Contacts SET "
                         "firstname=?, lastname=?,"
                         "phonenum=?, address=?,"
                         "email=? WHERE id=?;"; 
    
    SQLiteStatementHandle updateStatement(sqlStr, database.get()); 

    sqlite3_bind_text(updateStatement.get(), 1, c.firstName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(updateStatement.get(), 2, c.lastName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(updateStatement.get(), 3, c.phoneNumber.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(updateStatement.get(), 4, c.address.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(updateStatement.get(), 5, c.email.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(updateStatement.get(), 6, id);

    //execute SQL statement & check results
    int stepResult = sqlite3_step(updateStatement.get());
    
    if(stepResult != SQLITE_DONE)
    {
        return ErrorInfo(ERR_DATASOURCE_ERROR, "Could not update contact.");
    }

    notifyViews();

    return ErrorInfo(ERR_OK, "OK");
}

ErrorInfo SQLiteDataSource::deleteContact(Contact::ContactId id)
{

    //create sql prepared statement
    std::string sqlStr = "DELETE FROM Contacts WHERE id=?;"; 
    
    SQLiteStatementHandle deleteStatement(sqlStr, database.get()); 

    sqlite3_bind_int(deleteStatement.get(), 1, id);

    //execute SQL statement & check results
    int stepResult = sqlite3_step(deleteStatement.get());
    
    if(stepResult != SQLITE_DONE)
    {
        return ErrorInfo(ERR_DATASOURCE_ERROR, "Could not delete contact.");
    }

    notifyViews();

    return ErrorInfo(ERR_OK, "OK");
}


ErrorInfo SQLiteDataSource::deleteAllContacts()
{
    //create sql prepared statement
    std::string sqlStr = "DELETE FROM Contacts;"; 
    
    SQLiteStatementHandle deleteAllStatement(sqlStr, database.get()); 

    //execute SQL statement & check results
    int stepResult = sqlite3_step(deleteAllStatement.get());
    
    if(stepResult != SQLITE_DONE)
    {
        return ErrorInfo(ERR_DATASOURCE_ERROR, "Could not delete contacts.");
    }

    notifyViews();

    return ErrorInfo(ERR_OK, "OK");
}

