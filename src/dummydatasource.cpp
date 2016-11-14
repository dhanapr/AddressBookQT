
//dummydatasource.cpp
//Implementation of dummy data source class

#include <algorithm>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>

#include "addressbookmodel.h"
#include "dummydatasource.h"
#include "contact.h"


DummyDataSource::DummyDataSource()
{
    nextId = 1;

    std::stringstream ss;

    std::string temp;
    Contact c;
    
    for(int i=0; i < NUM_CONTACTS; i++)
    {
        ss << i+1; 

        temp = ss.str();
       // t=s.intmax_t();
        c.firstName = temp;
        c.lastName = temp;
        c.phoneNumber = temp;
        c.address = temp;
        c.email = temp;
        c.additionalInformation=temp;
    
        addContact(c);
        ss.str("");
    }
        
}

bool DummyDataSource::isViewRegistered(AddressBookView *viewToCheck)
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

void DummyDataSource::registerView(AddressBookView *viewToRegister)
{
    
    if(viewToRegister && !isViewRegistered(viewToRegister))
    {
        observerList.push_back(viewToRegister);
    }

}

void DummyDataSource::removeView(AddressBookView *viewToRemove)
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

void DummyDataSource::notifyViews()
{
    std::vector<AddressBookView*>::iterator it;

    for(it = observerList.begin(); it != observerList.end(); it++)
    {
        (*it)->updateView();
    }
}



ErrorInfo DummyDataSource::getContact(Contact::ContactId id, Contact &c)
{
    Contact::ContactRecordSet::iterator it;
    
    if(idExists(id, it))
    {
        c = *it;
        return ErrorInfo(ERR_OK, "OK");
    }
    else
    {
        return ErrorInfo(ERR_DATASOURCE_ERROR, "Contact could not be retrieved!");
    }

}

ErrorInfo DummyDataSource::getAllContacts(Contact::ContactRecordSet &rs)
{
    //Never returns false in this dummy class
    //Would return false in a real datasource if file could not be
    //opened or database could not be reached for example

    if(recordList.empty())
    {
        rs = Contact::ContactRecordSet();
        return ErrorInfo(ERR_OK, "OK");
    }
    else
    {
         rs = Contact::ContactRecordSet(recordList);
        return ErrorInfo(ERR_OK, "OK");
    }
}

ErrorInfo DummyDataSource::addContact(const Contact& c)
{
    Contact contactToAdd = c;
    contactToAdd.id = nextId;
    recordList.push_back(contactToAdd);
    nextId++;

    //Data has changed
    notifyViews();

    return ErrorInfo(ERR_OK, "OK");
}

ErrorInfo DummyDataSource::updateContact(Contact::ContactId id, const Contact& c)
{
    Contact::ContactRecordSet::iterator it;

    if(idExists(id, it))
    {
        *it = c;
        
        //Data has changed
        notifyViews();
        return ErrorInfo(ERR_OK, "OK");
    }
    else
    {
        //no item with that id
        return ErrorInfo(ERR_CONTACT_NOT_FOUND, "Contact id does not exist!");
    }
}

ErrorInfo DummyDataSource::deleteContact(Contact::ContactId id)
{
    Contact::ContactRecordSet::iterator itemToDeletePosition;

    if(idExists(id, itemToDeletePosition))
    {
        recordList.erase(itemToDeletePosition);
        
        //Data has changed
        notifyViews();
        return ErrorInfo(ERR_OK, "OK");
    }
    else
    {
        //item does not exist, cannot delete
        return ErrorInfo(ERR_CONTACT_NOT_FOUND, "Contact id does not exist!");
    }
}

ErrorInfo DummyDataSource::deleteAllContacts()
{
    recordList.clear();    

    notifyViews();
    return ErrorInfo(ERR_OK, "OK");
}

bool DummyDataSource::idExists(Contact::ContactId id, Contact::ContactRecordSet::iterator &pos)
{
    Contact::ContactRecordSet::iterator it;

    for(it = recordList.begin(); it != recordList.end(); it++)
    {
        //id found
        if(it->id == id)
        {
            pos = it;
            return true;

        }
    }

    //no item with that id exists
    //if loop has run it's course then it == recordList.end()
    pos = it;
    return false;
}
