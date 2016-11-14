#ifndef MODEL_DUMMYDATASOURCE_H
#define MODEL_DUMMYDATASOURCE_H

#include "addressbookmodel.h"
#include "addressbookview.h"
#include "contact.h"


const int NUM_CONTACTS = 5;

/************************************************************
    Class: DummyDataSource

    Author: Phil Grohe

    Mock object implementing the AddressBookModel interface.
    Creates a vector with dummy data when created.
    AddressBookModel interface methods act on this data rather
    than any kind of persistently stored data. Used as a 
    placeholder until AddressBookModel implementations providing
    true persistence are written (flat file, SQL, etc...)
************************************************************/

class DummyDataSource : public AddressBookModel
{
    public:
        //Data access services 
        virtual void registerView(AddressBookView *view);
        virtual void removeView(AddressBookView *view);
        virtual void notifyViews();

        virtual ErrorInfo getContact(Contact::ContactId id, Contact &c);
        virtual ErrorInfo getAllContacts(Contact::ContactRecordSet &rs);
        virtual ErrorInfo addContact(const Contact& c);
        virtual ErrorInfo updateContact(Contact::ContactId id, const Contact& c);
        virtual ErrorInfo deleteContact(Contact::ContactId id);
        virtual ErrorInfo deleteAllContacts();

        DummyDataSource();  
        ~DummyDataSource() { };

    private:
        bool isViewRegistered(AddressBookView *viewToCheck);
        bool idExists(Contact::ContactId id, Contact::ContactRecordSet::iterator &pos);

        Contact::ContactRecordSet recordList;
        Contact::ContactId nextId;

        std::vector<AddressBookView*> observerList;
};

#endif
