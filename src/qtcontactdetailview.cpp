#include "qtcontactdetailview.h"
#include "qtcontactform.h"
#include "qterrordialog.h"
#include "errorinfo.h"
//#include<qvalidator.h>
#include <string>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QGroupBox>

QtContactDetailView::QtContactDetailView(AddressBookModel& model, 
                    QWidget *parent) : 
                    QGroupBox("Contact Details", parent),
                    dataSource(model),
                    contactForm(new QtContactForm())
{

    contactForm->firstNameField->setReadOnly(true);
    contactForm->firstNameField->setStyleSheet("QLineEdit { background-color: blue }");
    contactForm->lastNameField->setReadOnly(true);
    contactForm->lastNameField->setStyleSheet("QLineEdit { background-color:blue  }");
    contactForm->addressField->setReadOnly(true);
    contactForm->addressField->setStyleSheet("QTextEdit { background-color: blue }");
    contactForm->phoneNumberField->setInputMask("9999999999");
    contactForm->phoneNumberField->setStyleSheet("QLineEdit { background-color: blue }");
    contactForm->phoneNumberField->setReadOnly(true);
    contactForm->emailField->setStyleSheet("QLineEdit { background-color:blue  }");
    contactForm->emailField->setReadOnly(true);
    contactForm->additionalInformation->setStyleSheet("QLineEdit { background-color:blue  }");
    contactForm->additionalInformation->setReadOnly(true);


    setLayout(contactForm);
    setFlat(false);
    
}

void QtContactDetailView::displayContact(Contact::ContactId id)
{
    Contact c;


    ErrorInfo getContactErrorStatus = dataSource.getContact(id, c);

    if(getContactErrorStatus.code != ERR_OK)
    {
        //could not fetch the contact
        //simply clear the fields
        clear();
        return;
    }
    else
    {

        contactForm->firstNameField->setText(c.firstName.c_str());
        contactForm->lastNameField->setText(c.lastName.c_str());
        contactForm->addressField->setPlainText(c.address.c_str());
        contactForm->phoneNumberField->setText(c.phoneNumber.c_str());
        contactForm->emailField->setText(c.email.c_str());
        contactForm->additionalInformation->setText(c.additionalInformation.c_str());

    }
}

void QtContactDetailView::clear()
{
    contactForm->clear();
}

