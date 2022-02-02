#include "componentwidget.h"

ComponentWidget::ComponentWidget(int id, QString name, ComponentType type, Model* model, QWidget *parent)
    :  QWidget(parent), name(name), type(type), id(id), model(model)
{
    vboxlayout = new QVBoxLayout(this);
    vboxlayout->setAlignment(Qt::Alignment(Qt::AlignmentFlag::AlignTop));

    memberLayout = new QVBoxLayout();

    nameLabel = new QLabel(name);
    parentClassLabel = new QLabel(componentTypeNameStrings[type]);
    QHBoxLayout* nameLayout = new QHBoxLayout();
    nameLayout->addWidget(nameLabel);
    nameLayout->addSpacerItem(new QSpacerItem(maximumWidth(),0,QSizePolicy::Maximum));
    nameLayout->addWidget(parentClassLabel);

    vboxlayout->addLayout(nameLayout);

    QPushButton* addnewmemberbutton = new QPushButton("Add new private member");
    connect(addnewmemberbutton,SIGNAL(clicked()),this,SLOT(onAddNewMemberClicked()));
    vboxlayout->addWidget(addnewmemberbutton);

    vboxlayout->addLayout(memberLayout);

    gridlayout = new QGridLayout();

    itemTypeLabel = new QLabel("Item type:");
    itemTypeLineEdit = new QLineEdit();
    gridlayout->addWidget(itemTypeLabel,0,0);
    gridlayout->addWidget(itemTypeLineEdit,0,1);

    connect(itemTypeLineEdit,SIGNAL(editingFinished()),this,SLOT(itemTypeChanged()));

    destructorLabel = new QLabel("Destructor:");
    destructorTextEdit = new PopUpTextEdit(DESTRUCTOR);
    gridlayout->addWidget(destructorLabel,100,0);
    gridlayout->addWidget(destructorTextEdit,100,1);

    connect(destructorTextEdit,SIGNAL(textChanged()),this,SLOT(popUpTextChanged()));

    vboxlayout->addLayout(gridlayout);
}

void ComponentWidget::onAddNewMemberClicked(){
    MemberWidget* member = new MemberWidget(model->createMember(this->id));
    memberLayout->addWidget(member);
    members.push_back(member);
    connect(member,SIGNAL(edited()),this,SLOT(memberChanged()));
    connect(member,SIGNAL(deleteMe()),this,SLOT(deleteMember()));
}

void ComponentWidget::deleteMember(){
    MemberWidget* member = qobject_cast<MemberWidget*>(sender());
    members.removeAll(member);
    memberLayout->removeWidget(member);
    model->deleteMember(this->id, member->getID());
    delete member;
}

void ComponentWidget::memberChanged(){
    MemberWidget* member = qobject_cast<MemberWidget*>(sender());
    model->modifyMember(this->id, member->getID(), member->getType(), member->getName());
}

void ComponentWidget::itemTypeChanged(){
    model->setItem(this->id,itemTypeLineEdit->text());
}

void ComponentWidget::popUpTextChanged(){
    PopUpTextEdit* popUpTextEdit = qobject_cast<PopUpTextEdit*>(sender());
    model->setMethod(this->id,popUpTextEdit->getMethodType(),popUpTextEdit->toPlainText());
}
