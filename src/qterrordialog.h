#ifndef VIEW_QTERRORDIALOG_H
#define VIEW_QTERRORDIALOG_H

#include <QMessageBox>

/***********************************************************************
    Class: QtErrorDialog

    Author: Phil Grohe

    Simple error dialog that will display an error message with an OK
    button.
***********************************************************************/

class QtErrorDialog : public QMessageBox 
{
    Q_OBJECT

    public:
        QtErrorDialog(std::string errMsg, QWidget *parent=0);
};

#endif
