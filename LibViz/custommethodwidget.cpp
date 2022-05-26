#include "custommethodwidget.h"

/*!
 * \brief Constructs a new Custom Method Widget object.
 * 
 * \param id The id of the custom method.
 * \param header The header of the custom method.
 * \param body The body of the custom method.
 * \param parent The parent widget.
 */
CustomMethodWidget::CustomMethodWidget(const int id, QString header, QString body, QWidget *parent) : QWidget(parent), id(id)
{
    hboxlayout = new QHBoxLayout(this);
    vboxlayout = new QVBoxLayout();
    hboxlayout->addLayout(vboxlayout);

    headerLineEdit = new QLineEdit();
    headerLineEdit->setPlaceholderText("Method header");
    bodyPopUpTextEdit = new PopUpTextEdit();
    bodyPopUpTextEdit->setPlaceholderText("Method body");
    vboxlayout->addWidget(headerLineEdit);
    vboxlayout->addWidget(bodyPopUpTextEdit);

    deleteButton = new QPushButton("X");
    deleteButton->setFixedWidth(20);
    deleteButton->setSizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Minimum);
    hboxlayout->addWidget(deleteButton);

    vboxlayout->setContentsMargins(0,0,0,0);
    hboxlayout->setContentsMargins(0,0,0,0);

    headerLineEdit->setText(header);
    bodyPopUpTextEdit->setText(body);

    connect(headerLineEdit,SIGNAL(editingFinished()),this,SIGNAL(edited()));
    connect(bodyPopUpTextEdit,SIGNAL(textChanged()),this,SIGNAL(edited()));
    connect(deleteButton,SIGNAL(clicked()),this,SIGNAL(deleteMe()));
}
