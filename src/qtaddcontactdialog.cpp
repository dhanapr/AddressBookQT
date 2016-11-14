#include "contact.h"
#include "qtaddcontactdialog.h"
#include <QDialog>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>


QtAddContactDialog::QtAddContactDialog(Contact &c, QWidget *parent, Qt::WindowFlags f) :
            QDialog(parent, f), contactForm(new QtContactForm()), outContact(c)
{
    QVBoxLayout *mainContainer = new QVBoxLayout();
    mainContainer->addLayout(contactForm);

    QHBoxLayout *buttonContainer = new QHBoxLayout();
    QPushButton *addButton = new QPushButton("Add");
    QPushButton *cancelButton = new QPushButton("Cancel");
    
    buttonContainer->addWidget(addButton);
    buttonContainer->addWidget(cancelButton);
    mainContainer->addLayout(buttonContainer);

    connect(addButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    setLayout(mainContainer);
    setWindowTitle("New Contact");
}

void QtAddContactDialog::accept()
{
    outContact.firstName = contactForm->firstNameField->text().toStdString();
    outContact.lastName = contactForm->lastNameField->text().toStdString();
    outContact.address = contactForm->addressField->toPlainText().toStdString();
    outContact.phoneNumber = contactForm->phoneNumberField->text().toStdString();
    outContact.email = contactForm->emailField->text().toStdString();
    outContact.additionalInformation = contactForm->additionalInformation->text().toStdString();
    QDialog::accept();
}
