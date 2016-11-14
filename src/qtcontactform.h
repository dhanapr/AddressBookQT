#ifndef VIEW_QTCONTACTFORM
#define VIEW_QTCONTACTFORM

#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>

/***********************************************************************
    Class: QtContactForm

    Author: Phil Grohe

    Qt FormLayout subclass that contains all the labels & line edits
    for displaying / entering a contact.

    Encapsulate the actual form fields themselves so they can easily
    all be instantiated without repeating boilerplate code.

    As this is a FormLayout subclass it is simply added to it's parent
    class like any other Qt Layout

    The actual line edit objects for the contact info are public so 
    as to be accessible.  Think of this as a kind of struct that just
    groups all the Contact form elements in one place
***********************************************************************/

class QtContactForm : public QFormLayout
{
    Q_OBJECT

    public:
        QtContactForm(QWidget *parent=0);

        void clear();

        QLineEdit *firstNameField;
        QLineEdit *lastNameField;
        QTextEdit *addressField;
        QLineEdit *phoneNumberField;
        QLineEdit *emailField;
        QLineEdit *additionalInformation;

};

#endif
