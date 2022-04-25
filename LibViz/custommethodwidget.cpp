#include "custommethodwidget.h"

CustomMethodWidget::CustomMethodWidget(const int id, QString header, QString body, QWidget *parent) : QWidget(parent), id(id)
{
    hboxlayout = new QVBoxLayout(this);
    headerLineEdit = new QLineEdit();
    headerLineEdit->setPlaceholderText("Method header");
    bodyPopUpTextEdit = new PopUpTextEdit();
    bodyPopUpTextEdit->setPlaceholderText("Method body");
    deleteButton = new QPushButton("X");
    hboxlayout->addWidget(headerLineEdit);
    hboxlayout->addWidget(bodyPopUpTextEdit);
    hboxlayout->addWidget(deleteButton);

    hboxlayout->setContentsMargins(0,0,0,0);

    headerLineEdit->setText(header);
    bodyPopUpTextEdit->setText(body);

    connect(headerLineEdit,SIGNAL(editingFinished()),this,SIGNAL(edited()));
    connect(bodyPopUpTextEdit,SIGNAL(textChanged()),this,SIGNAL(edited()));
    connect(deleteButton,SIGNAL(clicked()),this,SIGNAL(deleteMe()));
}
