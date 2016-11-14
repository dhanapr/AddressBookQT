#ifndef UI_QTCONTACTDETAIL_FORM
#define UI_QTCONTACTDETAIL_FORM

#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include "contact.h"
#include "addressbookmodel.h"
#include "qtcontactform.h"

/***********************************************************************
Class: QtContactDetailView

Author: Phil Grohe

Qt widget for displaying all the fields of a Contact.

Slot displayContact(Contact::ContactId id) receives the contact to
be displayed and 
***********************************************************************/

class QtContactDetailView : public QGroupBox
{
    Q_OBJECT

    public:
        QtContactDetailView(AddressBookModel &model, QWidget *parent=0);

        void clear();

    private slots:
        void displayContact(Contact::ContactId id);

    private:
        AddressBookModel &dataSource;
        QtContactForm* contactForm;
};
#endif
