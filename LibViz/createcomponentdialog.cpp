#include "createcomponentdialog.h"

/*!
 * \brief Constructs a new Create Component Widget object.
 * 
 * \param model 
 */
CreateComponentDialog::CreateComponentDialog(Model* model) : QDialog(), model(model)
{
    setWindowTitle("New component");

    okButton = new QPushButton("ok");
    cancelButton = new QPushButton("cancel");

    nameLineEdit = new QLineEdit();
    nameLineEdit->setPlaceholderText("name");

    componentTypeSelect = new QComboBox();
    componentTypeSelect->setPlaceholderText("type");

    errorLabel = new QLabel();
    errorLabel->setStyleSheet("color:red;");
    errorLabel->hide();

    foreach(ComponentType componentType, componentTypeNameStrings.keys()){
        componentTypeSelect->addItem(componentTypeNameStrings[componentType],componentType);
    }

    componentTypeSelect->addItem("Struct",-1);

    QVBoxLayout* vboxlayout = new QVBoxLayout(this);
    QHBoxLayout* hboxlayout = new QHBoxLayout();

    vboxlayout->addWidget(nameLineEdit);
    vboxlayout->addWidget(componentTypeSelect);
    vboxlayout->addWidget(errorLabel);
    vboxlayout->addLayout(hboxlayout);

    hboxlayout->addWidget(okButton);
    hboxlayout->addWidget(cancelButton);

    connect(okButton, SIGNAL(clicked()), this, SLOT(wantToAccept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

/*!
 * \brief Checks if the inputs in the dialog are valid.
 * 
 */
void CreateComponentDialog::wantToAccept(){
    bool acceptable = true;
    errorLabel->hide();
    nameLineEdit->setStyleSheet("");
    componentTypeSelect->setStyleSheet("");
    if(nameLineEdit->text() == ""){
        nameLineEdit->setStyleSheet("border:2px solid red;");
        errorLabel->setText("Please provide a name.");
        errorLabel->setHidden(false);
        acceptable = false;
    }
    if(componentTypeSelect->currentIndex() < 0){
        componentTypeSelect->setStyleSheet("border:2px solid red;");
        errorLabel->setText("Please provide a type.");
        errorLabel->setHidden(false);
        acceptable = false;
    }
    if(model->isComponentNameUsed(nameLineEdit->text())){
        nameLineEdit->setStyleSheet("border:2px solid red;");
        errorLabel->setText("The given name is already in use!");
        errorLabel->setHidden(false);
        acceptable = false;
    }
    if(acceptable){
        accept();
    }
}

/*!
 * \brief Clears the inputs in the dialog.
 * 
 */
void CreateComponentDialog::clear(){
    nameLineEdit->clear();
    componentTypeSelect->setCurrentIndex(-1);
    errorLabel->hide();
    nameLineEdit->setStyleSheet("");
    componentTypeSelect->setStyleSheet("");
}
