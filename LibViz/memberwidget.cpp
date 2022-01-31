#include "memberwidget.h"

MemberWidget::MemberWidget(const int id, QWidget *parent) : QWidget(parent), id(id)
{
    hboxlayout = new QHBoxLayout(this);
    type = new QLineEdit();
    type->setPlaceholderText("type");
    name = new QLineEdit();
    name->setPlaceholderText("name");
    hboxlayout->addWidget(type);
    hboxlayout->addWidget(name);

    hboxlayout->setContentsMargins(0,0,0,0);

    connect(type,SIGNAL(editingFinished()),this,SIGNAL(edited()));
    connect(name,SIGNAL(editingFinished()),this,SIGNAL(edited()));
}
