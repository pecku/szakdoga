#include "memberwidget.h"

/*!
 * \brief Constructs a new Member Widget object.
 * 
 * \param id The id of the member.
 * \param type The type of the member.
 * \param name The name of the member.
 * \param parent The parent widget.
 */
MemberWidget::MemberWidget(const int id, QString type, QString name, QWidget *parent) : QWidget(parent), id(id)
{
    hboxlayout = new QHBoxLayout(this);
    typeLineEdit = new QLineEdit();
    typeLineEdit->setPlaceholderText("type");
    nameLineEdit = new QLineEdit();
    nameLineEdit->setPlaceholderText("name");
    deleteButton = new QPushButton("X");
    deleteButton->setMaximumWidth(30);
    hboxlayout->addWidget(typeLineEdit);
    hboxlayout->addWidget(nameLineEdit);
    hboxlayout->addWidget(deleteButton);

    hboxlayout->setContentsMargins(0,0,0,0);

    typeLineEdit->setText(type);
    nameLineEdit->setText(name);

    connect(typeLineEdit,SIGNAL(editingFinished()),this,SIGNAL(edited()));
    connect(nameLineEdit,SIGNAL(editingFinished()),this,SIGNAL(edited()));
    connect(deleteButton,SIGNAL(clicked()),this,SIGNAL(deleteMe()));
}
