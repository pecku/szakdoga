#include "structwidget.h"

StructWidget::StructWidget(int id, QString name, Model* model, QWidget *parent)
    : QWidget(parent), name(name), id(id), model(model)
{
    vboxlayout = new QVBoxLayout(this);
    vboxlayout->setAlignment(Qt::Alignment(Qt::AlignmentFlag::AlignTop));

    memberLayout = new QVBoxLayout();
    customMethodLayout = new QVBoxLayout();

    QPushButton* addnewmemberbutton = new QPushButton("Add new private member");
    connect(addnewmemberbutton,SIGNAL(clicked()),this,SLOT(onAddNewMemberClicked()));
    vboxlayout->addWidget(addnewmemberbutton);
    QPushButton* addnewcustommethodbutton = new QPushButton("Add new method");
    connect(addnewcustommethodbutton,SIGNAL(clicked()),this,SLOT(onAddNewMethodClicked()));
    vboxlayout->addWidget(addnewcustommethodbutton);

    vboxlayout->addLayout(memberLayout);
    vboxlayout->addLayout(customMethodLayout);
}

void StructWidget::onAddNewMemberClicked(){
    MemberWidget* member = new MemberWidget(model->createMember(this->id));
    memberLayout->addWidget(member);
    members.push_back(member);
    connect(member,SIGNAL(edited()),this,SLOT(memberChanged()));
    connect(member,SIGNAL(deleteMe()),this,SLOT(deleteMember()));
}

void StructWidget::deleteMember(){
    MemberWidget* member = qobject_cast<MemberWidget*>(sender());
    members.removeAll(member);
    memberLayout->removeWidget(member);
    model->deleteMember(this->id, member->getID());
    delete member;
}

void StructWidget::memberChanged(){
    MemberWidget* member = qobject_cast<MemberWidget*>(sender());
    model->modifyMember(this->id, member->getID(), member->getType(), member->getName());
}

void StructWidget::onAddNewMethodClicked(){
    CustomMethodWidget* customMethod = new CustomMethodWidget(model->createCustomMethod(this->id));
    customMethodLayout->addWidget(customMethod);
    customMethods.push_back(customMethod);
    connect(customMethod,SIGNAL(edited()),this,SLOT(methodChanged()));
    connect(customMethod,SIGNAL(deleteMe()),this,SLOT(deleteMethod()));
}

void StructWidget::deleteMethod(){
    CustomMethodWidget* customMethod = qobject_cast<CustomMethodWidget*>(sender());
    customMethods.removeAll(customMethod);
    customMethodLayout->removeWidget(customMethod);
    model->deleteCustomMethod(this->id, customMethod->getID());
    delete customMethod;
}

void StructWidget::methodChanged(){
    CustomMethodWidget* customMethod = qobject_cast<CustomMethodWidget*>(sender());
    model->modifyCustomMethod(this->id, customMethod->getID(), customMethod->getHeader(), customMethod->getBody());
}
