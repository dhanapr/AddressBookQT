#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QFormLayout>
#include "qtcontactform.h"



QtContactForm::QtContactForm(QWidget *parent) : 
        QFormLayout(parent), firstNameField(new QLineEdit()),
        lastNameField(new QLineEdit()),
        addressField(new QTextEdit()),
        phoneNumberField(new QLineEdit()),
        emailField(new QLineEdit()),additionalInformation(new QLineEdit())
{
    addRow("First Name", firstNameField);
    addRow("Last Name", lastNameField);
    addRow("Address", addressField);
    addRow("Phone Number", phoneNumberField);
    addRow("Email", emailField);
    addRow("Additional Information",additionalInformation);
}

void QtContactForm::clear()
{
    firstNameField->setText("");
    lastNameField->setText("");
    addressField->setPlainText("");
    phoneNumberField->setText("");
    emailField->setText("");
    additionalInformation->setText("");
}
