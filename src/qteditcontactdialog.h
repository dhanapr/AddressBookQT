#ifndef VIEW_QTEDITCONTACTDIALOG_H
#define VIEW_QTEDITCONTACTDIALOG_H

#include <QDialog>
#include <QWidget>
#include "qtcontactform.h"
#include "contact.h"

/***********************************************************************
    Class: QtEditContactDialog

    Author: Phil Grohe
    
    Qt Dialog presenting a form to edit an existing contact
***********************************************************************/

class QtEditContactDialog : public QDialog
{
    Q_OBJECT

    public:
        QtEditContactDialog(Contact &c, QWidget *parent=0, Qt::WindowFlags f=0);

    public slots:
        void accept();

    private:
        void fillForm();

        QtContactForm *contactForm;
        Contact &contactToEdit;

};

#endif
