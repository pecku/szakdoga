#include "structwidget.h"

StructWidget::StructWidget(int id, QString name, Model* model, QWidget *parent)
    : QWidget(parent), name(name), id(id), model(model)
{
    vboxlayout = new QVBoxLayout(this);
    vboxlayout->setAlignment(Qt::Alignment(Qt::AlignmentFlag::AlignTop));

    memberLayout = new QVBoxLayout();
    customMethodLayout = new QVBoxLayout();

    nameLabel = new QLabel(name);
    structLabel = new QLabel("struct");
    QHBoxLayout* nameLayout = new QHBoxLayout();
    nameLayout->addWidget(nameLabel);
    nameLayout->addSpacerItem(new QSpacerItem(maximumWidth(),0,QSizePolicy::Maximum));
    nameLayout->addWidget(structLabel);

    vboxlayout->addLayout(nameLayout);

    QPushButton* addnewmemberbutton = new QPushButton("Add new member");
    connect(addnewmemberbutton,SIGNAL(clicked()),this,SLOT(onAddNewMemberClicked()));
    vboxlayout->addWidget(addnewmemberbutton);
    QPushButton* addnewcustommethodbutton = new QPushButton("Add new method");
    connect(addnewcustommethodbutton,SIGNAL(clicked()),this,SLOT(onAddNewMethodClicked()));
    vboxlayout->addWidget(addnewcustommethodbutton);

    vboxlayout->addLayout(memberLayout);
    vboxlayout->addLayout(customMethodLayout);
}

StructWidget::StructWidget(const Struct& _struct, Model* model, QWidget *parent) : StructWidget(_struct.getID(), _struct.getName(), model, parent)
{
    createMembers(_struct.getMembers());
    createCustomMethods(_struct.getCustomMethods());
}

void StructWidget::onAddNewMemberClicked(){
    createMember(model->createMember(this->id));
}

void StructWidget::createMember(int id, QString type, QString name){
    MemberWidget* member = new MemberWidget(id, type, name);
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
    createCustomMethod(model->createCustomMethod(this->id));
}

void StructWidget::createCustomMethod(int id, QString header, QString body){
    CustomMethodWidget* customMethod = new CustomMethodWidget(id, header, body);
    customMethodLayout->addWidget(customMethod);
    customMethods.push_back(customMethod);
    connect(customMethod,SIGNAL(edited()),this,SLOT(methodChanged()));
    connect(customMethod,SIGNAL(deleteMe()),this,SLOT(deleteMethod()));
}

void StructWidget::createMembers(QMap<int, Member> members){
    foreach(Member member, members){
        createMember(member.id, member.type, member.name);
    }
}

void StructWidget::createCustomMethods(QMap<int, CustomMethod> customMethods){
    foreach(CustomMethod customMethod, customMethods){
        createCustomMethod(customMethod.id, customMethod.header, customMethod.body);
    }
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
