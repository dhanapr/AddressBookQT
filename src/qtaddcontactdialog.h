#ifndef VIEW_QTADDCONTACTDIALOG_H
#define VIEW_QTADDCONTACTDIALOG_H

#include <QDialog>
#include <QWidget>
#include "qtcontactform.h"
#include "contact.h"

/***********************************************************************
    Class: QtAddContactDialog

    Author: Phil Grohe

    Qt Dialog presenting a form to add a new contact.    
***********************************************************************/

class QtAddContactDialog : public QDialog
{

    Q_OBJECT 

    public:
        QtAddContactDialog(Contact &c, QWidget *parent=0, Qt::WindowFlags f=0);

    public slots:
        void accept();

    private:
        QtContactForm *contactForm;
        Contact &outContact;
};

#endif
