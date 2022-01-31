#include "textinputdialog.h"

TextInputDialog::TextInputDialog()
{
    saveButton = new QPushButton("Save");
    cancelButton = new QPushButton("Cancel");

    textEdit = new QTextEdit;

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);

    QVBoxLayout* vboxlayout = new QVBoxLayout(this);
    vboxlayout->addWidget(textEdit);
    vboxlayout->addLayout(buttonLayout);

    connect(saveButton,SIGNAL(clicked()),this,SLOT(accept()));
    connect(cancelButton,SIGNAL(clicked()),this,SLOT(reject()));
}

