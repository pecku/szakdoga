#include "memberwidget.h"

MemberWidget::MemberWidget(const int id, QWidget *parent) : QWidget(parent), id(id)
{
    hboxlayout = new QHBoxLayout(this);
    type = new QLineEdit();
    type->setPlaceholderText("type");
    name = new QLineEdit();
    name->setPlaceholderText("name");
    deleteButton = new QPushButton("X");
    deleteButton->setMaximumWidth(30);
    hboxlayout->addWidget(type);
    hboxlayout->addWidget(name);
    hboxlayout->addWidget(deleteButton);

    hboxlayout->setContentsMargins(0,0,0,0);

    connect(type,SIGNAL(editingFinished()),this,SIGNAL(edited()));
    connect(name,SIGNAL(editingFinished()),this,SIGNAL(edited()));
    connect(deleteButton,SIGNAL(clicked()),this,SIGNAL(deleteMe()));
}
