#include "createcomponentdialog.h"

CreateComponentDialog::CreateComponentDialog() : QDialog()
{
    okButton = new QPushButton("ok");
    cancelButton = new QPushButton("cancel");

    nameLineEdit = new QLineEdit();
    nameLineEdit->setPlaceholderText("name");

    componentTypeSelect = new QComboBox();
    componentTypeSelect->setPlaceholderText("type");

    QVBoxLayout* vboxlayout = new QVBoxLayout(this);
    QHBoxLayout* hboxlayout = new QHBoxLayout();

    vboxlayout->addWidget(nameLineEdit);
    vboxlayout->addWidget(componentTypeSelect);
    vboxlayout->addLayout(hboxlayout);

    hboxlayout->addWidget(okButton);
    hboxlayout->addWidget(cancelButton);

    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

void CreateComponentDialog::setMode(CreateComponentDialogMode mode){
    if(this->mode == mode) return;
    this->mode = mode;
    switch (mode) {
        case PROCEDURE:{
            componentTypeSelect->clear();
            auto prockeys = procedureTypeNameStrings.keys();
            for(ProcedureType proctype : prockeys){
                componentTypeSelect->addItem(procedureTypeNameStrings[proctype],proctype);
            }
            break;
        }
        case ENUMERATOR:{
            componentTypeSelect->clear();
            auto enorkeys = enumeratorTypeNameStrings.keys();
            for(EnumeratorType enortype : enorkeys){
                componentTypeSelect->addItem(enumeratorTypeNameStrings[enortype],enortype);
            }
            break;
        }
    }
}

void CreateComponentDialog::clear(){
    nameLineEdit->clear();
    componentTypeSelect->setCurrentIndex(-1);
}
