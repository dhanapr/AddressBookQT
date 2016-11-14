#ifndef MODEL_SQLITE_DATASOURCE_H
#define MODEL_SQLITE_DATASOURCE_H

#include <sqlite3.h>
#include <string>
#include <vector>
#include <Qsql>
#include <QsqlDatabase>
#include "addressbookmodel.h"
#include "addressbookview.h"
#include "contact.h"
#include "sqliteutils.h"

/***********************************************************************
    Class: SQLiteDataSource

    Author: Phil Grohe

    A SQLite driven backend for the address book. Implements the
    AddressBookModel interface.
***********************************************************************/

class SQLiteDataSource : public AddressBookModel
{
    public:
        SQLiteDataSource(const std::string& filename, bool createDB);
        ~SQLiteDataSource();

        //AddressBookModel interface
        virtual void registerView(AddressBookView *viewToRegister);
        virtual void removeView(AddressBookView *viewToRemove);
        virtual void notifyViews();
        virtual ErrorInfo getContact(Contact::ContactId id, Contact& c);
        virtual ErrorInfo getAllContacts(Contact::ContactRecordSet &rs);
        virtual ErrorInfo addContact(const Contact& c);
        virtual ErrorInfo updateContact(Contact::ContactId id, const Contact&);
        virtual ErrorInfo deleteContact(Contact::ContactId id);
        virtual ErrorInfo deleteAllContacts();
  virtual ErrorInfo searchContact(const Contact& c);
    private:
        void createTable();
        void fillContactFromRow(sqlite3_stmt *s, Contact &c);

        bool isViewRegistered(AddressBookView *viewToCheck);

        std::string dbFilename;
        SQLiteDBHandle database;
        std::vector<AddressBookView*> observerList;

};

#endif
