#ifndef UI_MAINWINDOW
#define UI_MAINWINDOW

#include<QtWidgets/QMainWindow>
#include<QtWidgets/QPushButton>
#include "addressbookcontroller.h"
#include "addressbookmodel.h"
#include "addressbookview.h"
#include "qtcontactlist.h"
#include "qtcontactdetailview.h"

/***********************************************************************
    Class: QtAddressBookGUI

    Author: Phil Grohe

    Top level application window.  Instantiates sub widgets and connects
    their signals and slots.
***********************************************************************/

class QtAddressBookGUI : public QMainWindow, public AddressBookView
{
    Q_OBJECT

    public:
        QtAddressBookGUI(AddressBookController &controller, AddressBookModel &model, 
        QWidget *parent=0, Qt::WindowFlags flags=0);


        //AddressBookView interface
        virtual void updateView();
        virtual void showUI();
        virtual ~QtAddressBookGUI();

    signals:
        void pullDataFromModel();

    private slots:
        void addContact();
        void deleteSure();
        void deleteContact();
        void editContact();
        void searchContact();

    private:
        void createWidgets();

        QtContactList *list;
        QtContactDetailView *detailView;

        QPushButton *newContactButton;
        QPushButton *editContactButton;
        QPushButton *deleteContactButton;
        QPushButton *searchContactButton;

        AddressBookController& appController;
        AddressBookModel& dataSource;
}; 

#endif
