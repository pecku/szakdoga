#include "memberwidget.h"

MemberWidget::MemberWidget(QWidget *parent) : QWidget(parent)
{
    hboxlayout = new QHBoxLayout(this);
    type = new QLineEdit();
    type->setPlaceholderText("type");
    name = new QLineEdit();
    name->setPlaceholderText("name");
    hboxlayout->addWidget(type);
    hboxlayout->addWidget(name);

    hboxlayout->setContentsMargins(0,0,0,0);
}
