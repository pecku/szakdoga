#include "settingsdialog.h"

SettingsDialog::SettingsDialog()
{
    okButton = new QPushButton("ok");
    cancelButton = new QPushButton("cancel");

    compilerPathLineEdit = new QLineEdit();
    compilerPathLineEdit->setPlaceholderText("Compiler path");

    argumentsLineEdit = new QLineEdit();
    argumentsLineEdit->setPlaceholderText("Compiler arguments");

    QVBoxLayout* vboxlayout = new QVBoxLayout(this);
    QHBoxLayout* hboxlayout = new QHBoxLayout();

    vboxlayout->addWidget(compilerPathLineEdit);
    vboxlayout->addWidget(argumentsLineEdit);
    vboxlayout->addLayout(hboxlayout);

    hboxlayout->addWidget(okButton);
    hboxlayout->addWidget(cancelButton);

    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}
