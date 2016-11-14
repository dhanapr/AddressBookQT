#include "addressbookview.h"
#include "addressbookmodel.h"
#include "addressbookcontroller.h"
#include "qtaddressbookgui.h"
#include "errorinfo.h"
#include "contact.h"

AddressBookController::AddressBookController(AddressBookModel &d) : dataStore(d)
{
    frontEnd = new QtAddressBookGUI(*this, dataStore);
    dataStore.registerView(frontEnd);

}

void AddressBookController::start()
{
    frontEnd->showUI();
}

AddressBookController::~AddressBookController()
{
    delete frontEnd;
}

ErrorInfo AddressBookController::submitContact(const Contact &c)
{    
    
    if(!c.isValidToAdd())
    {
        return ErrorInfo(ERR_CONTACT_NOT_VALID,
                        "Invalid Contact. Make sure all required fields are filled.");
    }
    if(!c.isValidToPhonenumber())
    {
        return ErrorInfo(ERR_CONTACT_NOT_VALID,
                        "Invalid Phone number");
    }

    return dataStore.addContact(c);
    if(!c.isValidToEmail())
    {
        return ErrorInfo(ERR_CONTACT_NOT_VALID,
                                "Invalid Email ID");
            }
    
}

ErrorInfo AddressBookController::deleteContact(const Contact::ContactId id)
{
    return dataStore.deleteContact(id);

}

ErrorInfo AddressBookController::editContact(const Contact::ContactId id, const Contact &c)
{
    if(!c.isValidToAdd())
    {
        return ErrorInfo(ERR_CONTACT_NOT_VALID, 
                "Invalid Contact. Make sure all required fields are filled.");
    }

    return dataStore.updateContact(id, c);

}

ErrorInfo AddressBookController::searchContact( const Contact &c)
{
    if(!c.isValidToSearch())
    {
        return ErrorInfo(ERR_CONTACT_NOT_VALID,
                "No files found with the name");
    }

    return dataStore.searchContact(c);

}
