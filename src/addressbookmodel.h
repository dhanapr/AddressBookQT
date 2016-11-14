#ifndef MODEL_ADDRESSBOOK_MODEL_H
#define MODEL_ADDRESSBOOK_MODEL_H

#include "contact.h"
#include "errorinfo.h"
#include "addressbookview.h"

/***********************************************************************
    Class: AddressBookModel

    Author: Phil Grohe

    Interface class for the data storage back end of the addressbook.
    Provides services for basic retrieval and updating of the contact 
    list.

    This our Model class in an MVC architecture.  As such
    it provides an interface to register/unregister/notify observers.
    
    Different types of backend storage solutions (flat file, SQL,
    , web based API etc...) for the address book must implement this 
    interface.
***********************************************************************/
class AddressBookModel
{

    public:

        virtual void registerView(AddressBookView *viewToRegister)=0;
        virtual void removeView(AddressBookView *viewToRemove)=0;
        virtual void notifyViews()=0;

        virtual ErrorInfo getContact(Contact::ContactId id, Contact& c) = 0;
        virtual ErrorInfo getAllContacts(Contact::ContactRecordSet &rs) = 0;
        virtual ErrorInfo addContact(const Contact& c) = 0;
        virtual ErrorInfo updateContact(Contact::ContactId id, const Contact& c) = 0;
        virtual ErrorInfo deleteContact(Contact::ContactId id)=0;
        virtual ErrorInfo deleteAllContacts()=0;
virtual ErrorInfo searchContact(const Contact& c) = 0;
        virtual ~AddressBookModel() {};

};

#endif
