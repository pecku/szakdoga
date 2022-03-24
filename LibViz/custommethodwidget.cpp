#include "custommethodwidget.h"

CustomMethodWidget::CustomMethodWidget(const int id, QWidget *parent) : QWidget(parent), id(id)
{
    hboxlayout = new QVBoxLayout(this);
    header = new QLineEdit();
    header->setPlaceholderText("Method header");
    body = new PopUpTextEdit();
    body->setPlaceholderText("Method body");
    deleteButton = new QPushButton("X");
    hboxlayout->addWidget(header);
    hboxlayout->addWidget(body);
    hboxlayout->addWidget(deleteButton);

    hboxlayout->setContentsMargins(0,0,0,0);

    connect(header,SIGNAL(editingFinished()),this,SIGNAL(edited()));
    connect(body,SIGNAL(textChanged()),this,SIGNAL(edited()));
    connect(deleteButton,SIGNAL(clicked()),this,SIGNAL(deleteMe()));
}
