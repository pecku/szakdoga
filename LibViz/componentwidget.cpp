#include "componentwidget.h"

ComponentWidget::ComponentWidget(int id, QString name, ComponentType type, Model* model, QWidget *parent)
    :  QWidget(parent), name(name), type(type), id(id), model(model)
{
    objectNameApproved = true;

    vboxlayout = new QVBoxLayout(this);
    vboxlayout->setAlignment(Qt::Alignment(Qt::AlignmentFlag::AlignTop));

    memberLayout = new QVBoxLayout();
    customMethodLayout = new QVBoxLayout();

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
    QPushButton* addnewcustommethodbutton = new QPushButton("Add new method");
    connect(addnewcustommethodbutton,SIGNAL(clicked()),this,SLOT(onAddNewMethodClicked()));
    vboxlayout->addWidget(addnewcustommethodbutton);

    vboxlayout->addLayout(memberLayout);

    gridlayout = new QGridLayout();

    objectNameLabel = new QLabel("Object name:");
    objectNameLineEdit = new QLineEdit();
    gridlayout->addWidget(objectNameLabel,0,0);
    gridlayout->addWidget(objectNameLineEdit,0,1);

    itemTypeLabel = new QLabel("Item type:");
    itemTypeLineEdit = new QLineEdit();
    gridlayout->addWidget(itemTypeLabel,1,0);
    gridlayout->addWidget(itemTypeLineEdit,1,1);

    destructorLabel = new QLabel("Destructor:");
    destructorTextEdit = new PopUpTextEdit(DESTRUCTOR);
    gridlayout->addWidget(destructorLabel,100,0);
    gridlayout->addWidget(destructorTextEdit,100,1);

    vboxlayout->addLayout(gridlayout);
    vboxlayout->addLayout(customMethodLayout);
}

void ComponentWidget::connectSignals(){
    connect(objectNameLineEdit,SIGNAL(editingFinished()),this,SLOT(objectNameChanged()));
    connect(itemTypeLineEdit,SIGNAL(editingFinished()),this,SLOT(itemTypeChanged()));
    connect(destructorTextEdit,SIGNAL(textChanged()),this,SLOT(popUpTextChanged()));
}

bool ComponentWidget::checkRequiredBase(){
    bool allgood = true;
    objectNameLineEdit->setStyleSheet("");
    if(objectNameLineEdit->text() == "" || !objectNameApproved){
        objectNameLineEdit->setStyleSheet("border:2px solid red;");
        allgood = false;
    }
    itemTypeLineEdit->setStyleSheet("");
    if(itemTypeLineEdit->text() == ""){
        itemTypeLineEdit->setStyleSheet("border:2px solid red;");
        allgood = false;
    }
    return allgood;
}

void ComponentWidget::onAddNewMemberClicked(){
    createMember(model->createMember(this->id));
}

void ComponentWidget::createMember(int id, QString type, QString name){
    MemberWidget* member = new MemberWidget(id, type, name);
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

void ComponentWidget::onAddNewMethodClicked(){
    createCustomMethod(model->createCustomMethod(this->id));
}

void ComponentWidget::createCustomMethod(int id, QString header, QString body){
    CustomMethodWidget* customMethod = new CustomMethodWidget(id, header, body);
    customMethodLayout->addWidget(customMethod);
    customMethods.push_back(customMethod);
    connect(customMethod,SIGNAL(edited()),this,SLOT(methodChanged()));
    connect(customMethod,SIGNAL(deleteMe()),this,SLOT(deleteMethod()));
}

void ComponentWidget::deleteMethod(){
    CustomMethodWidget* customMethod = qobject_cast<CustomMethodWidget*>(sender());
    customMethods.removeAll(customMethod);
    customMethodLayout->removeWidget(customMethod);
    model->deleteCustomMethod(this->id, customMethod->getID());
    delete customMethod;
}

void ComponentWidget::createMembers(QMap<int, Member> members){
    foreach(Member member, members){
        createMember(member.id, member.type, member.name);
    }
}

void ComponentWidget::createCustomMethods(QMap<int, CustomMethod> customMethods){
    foreach(CustomMethod customMethod, customMethods){
        createCustomMethod(customMethod.id, customMethod.header, customMethod.body);
    }
}

void ComponentWidget::methodChanged(){
    CustomMethodWidget* customMethod = qobject_cast<CustomMethodWidget*>(sender());
    model->modifyCustomMethod(this->id, customMethod->getID(), customMethod->getHeader(), customMethod->getBody());
}

void ComponentWidget::objectNameChanged(){
    QString objectName = objectNameLineEdit->text();
    objectNameLineEdit->setStyleSheet("");
    objectNameLineEdit->setToolTip("");
    if(model->isObjectNameUsed(objectName) || model->isComponentNameUsed(objectName)){
        objectNameLineEdit->setStyleSheet("border:2px solid red;");
        objectNameLineEdit->setToolTip("Object name already in use!");
        QWhatsThis::showText(mapToGlobal(objectNameLineEdit->pos()+QPoint(0,objectNameLineEdit->height())), "Object name already in use!");
        objectNameApproved = false;
    }else{
        model->setObjectName(this->id,objectNameLineEdit->text());
        objectNameApproved = true;
    }
}

void ComponentWidget::itemTypeChanged(){
    model->setItem(this->id,itemTypeLineEdit->text());
}

void ComponentWidget::popUpTextChanged(){
    PopUpTextEdit* popUpTextEdit = qobject_cast<PopUpTextEdit*>(sender());
    model->setMethod(this->id,popUpTextEdit->getMethodType(),popUpTextEdit->toPlainText());
}
