#include "qterrordialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

QtErrorDialog::QtErrorDialog(std::string errMsg, QWidget *parent) :
                        QMessageBox(QMessageBox::Warning, "An error occured...", 
                        errMsg.c_str(), QMessageBox::Ok, parent){}

/*{
    QVBoxLayout *mainContainer = new QVBoxLayout();
    setLayout(mainContainer);
    
    QHBoxLayout *buttonContainer = new QHBoxLayout();
    QHBoxLayout *labelContainer = new QHBoxLayout();
  
    QLabel *errorMsg = new QLabel(errMsg.c_str());
    QPushButton *okButton = new QPushButton("Ok");

    buttonContainer->addWidget(okButton);
    labelContainer->addWidget(errorMsg);

    mainContainer->addLayout(labelContainer);
    mainContainer->addLayout(buttonContainer);

    connect(okButton, SIGNAL(clicked()),
            this, SLOT(accept()));

}*/
