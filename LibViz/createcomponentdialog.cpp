#include "createcomponentdialog.h"

CreateComponentDialog::CreateComponentDialog() : QDialog()
{
    okButton = new QPushButton("ok");
    cancelButton = new QPushButton("cancel");

    nameLineEdit = new QLineEdit();
    nameLineEdit->setPlaceholderText("name");

    componentTypeSelect = new QComboBox();
    componentTypeSelect->setPlaceholderText("type");

    foreach(ComponentType componentType, componentTypeNameStrings.keys()){
        componentTypeSelect->addItem(componentTypeNameStrings[componentType],componentType);
    }

    QVBoxLayout* vboxlayout = new QVBoxLayout(this);
    QHBoxLayout* hboxlayout = new QHBoxLayout();

    vboxlayout->addWidget(nameLineEdit);
    vboxlayout->addWidget(componentTypeSelect);
    vboxlayout->addLayout(hboxlayout);

    hboxlayout->addWidget(okButton);
    hboxlayout->addWidget(cancelButton);

    connect(okButton, SIGNAL(clicked()), this, SLOT(wantToAccept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

void CreateComponentDialog::wantToAccept(){
    bool acceptable = true;
    nameLineEdit->setStyleSheet("");
    componentTypeSelect->setStyleSheet("");
    if(nameLineEdit->text() == ""){
        nameLineEdit->setStyleSheet("border:2px solid red;");
        acceptable = false;
    }
    if(componentTypeSelect->currentIndex() < 0){
        componentTypeSelect->setStyleSheet("border:2px solid red;");
        acceptable = false;
    }
    if(acceptable){
        accept();
    }
}

void CreateComponentDialog::clear(){
    nameLineEdit->clear();
    componentTypeSelect->setCurrentIndex(-1);
}
