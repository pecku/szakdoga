#include "componentwidget.h"

/*!
 * \brief Constructs a new Component Widget object.
 * 
 * \param id The id of the component.
 * \param name The name of the component.
 * \param type The type of the component.
 * \param model The model object that stores the component.
 * \param parent The parent of the widget.
 */
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

    constructorParameterLabel = new QLabel("Constructor parameter:");
    constructorParameterLineEdit = new QLineEdit();
    gridlayout->addWidget(constructorParameterLabel,2,0);
    gridlayout->addWidget(constructorParameterLineEdit,2,1);

    destructorLabel = new QLabel("Destructor:");
    destructorTextEdit = new PopUpTextEdit(DESTRUCTOR);
    gridlayout->addWidget(destructorLabel,100,0);
    gridlayout->addWidget(destructorTextEdit,100,1);

    vboxlayout->addLayout(gridlayout);
    vboxlayout->addLayout(customMethodLayout);
}

/*!
 * \brief Connects the signals of members to the correct slots.
 * 
 */
void ComponentWidget::connectSignals(){
    connect(objectNameLineEdit,SIGNAL(editingFinished()),this,SLOT(objectNameChanged()));
    connect(itemTypeLineEdit,SIGNAL(editingFinished()),this,SLOT(itemTypeChanged()));
    connect(constructorParameterLineEdit,SIGNAL(editingFinished()),this,SLOT(constructorParameterChanged()));
    connect(destructorTextEdit,SIGNAL(textChanged()),this,SLOT(popUpTextChanged()));
}

/*!
 * \brief Checks if the required fields are filled in. (This is a base method for use by child classes)
 * 
 * \return true 
 * \return false 
 */
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

/*!
 * \brief Slot for when the 'Add new private member' button is clicked.
 * 
 */
void ComponentWidget::onAddNewMemberClicked(){
    createMember(model->createMember(this->id));
}

/*!
 * \brief Creates a new member widget.
 * 
 * \param id The id of the member.
 * \param type The type of the member.
 * \param name The name of the member.
 */
void ComponentWidget::createMember(int id, QString type, QString name){
    MemberWidget* member = new MemberWidget(id, type, name);
    memberLayout->addWidget(member);
    members.push_back(member);
    connect(member,SIGNAL(edited()),this,SLOT(memberChanged()));
    connect(member,SIGNAL(deleteMe()),this,SLOT(deleteMember()));
}

/*!
 * \brief Deletes the member widget which the signal came from.
 * 
 */
void ComponentWidget::deleteMember(){
    MemberWidget* member = qobject_cast<MemberWidget*>(sender());
    members.removeAll(member);
    memberLayout->removeWidget(member);
    model->deleteMember(this->id, member->getID());
    delete member;
}

/*!
 * \brief Slot for modifying a member object stored in the model corresponding to the changed member widget.
 * 
 */
void ComponentWidget::memberChanged(){
    MemberWidget* member = qobject_cast<MemberWidget*>(sender());
    model->modifyMember(this->id, member->getID(), member->getType(), member->getName());
}

/*!
 * \brief Slot for when the 'Add new method' button is clicked.
 * 
 */
void ComponentWidget::onAddNewMethodClicked(){
    createCustomMethod(model->createCustomMethod(this->id));
}

/*!
 * \brief Creates a new custom method widget.
 * 
 * \param id The id of the custom method.
 * \param header The header of the custom method.
 * \param body The body of the custom method.
 */
void ComponentWidget::createCustomMethod(int id, QString header, QString body){
    CustomMethodWidget* customMethod = new CustomMethodWidget(id, header, body);
    customMethodLayout->addWidget(customMethod);
    customMethods.push_back(customMethod);
    connect(customMethod,SIGNAL(edited()),this,SLOT(methodChanged()));
    connect(customMethod,SIGNAL(deleteMe()),this,SLOT(deleteMethod()));
}

/*!
 * \brief Deletes the custom method widget which the signal came from.
 * 
 */
void ComponentWidget::deleteMethod(){
    CustomMethodWidget* customMethod = qobject_cast<CustomMethodWidget*>(sender());
    customMethods.removeAll(customMethod);
    customMethodLayout->removeWidget(customMethod);
    model->deleteCustomMethod(this->id, customMethod->getID());
    delete customMethod;
}

/*!
 * \brief Creates member widgets from a map of ids and member objects.
 * 
 * \param members Map of ids and member objects.
 */
void ComponentWidget::createMembers(QMap<int, Member> members){
    foreach(Member member, members){
        createMember(member.id, member.type, member.name);
    }
}

/*!
 * \brief Creates custom method widgets from a map of ids and custom method objects.
 * 
 * \param customMethods Map of ids and custom method objects.
 */
void ComponentWidget::createCustomMethods(QMap<int, CustomMethod> customMethods){
    foreach(CustomMethod customMethod, customMethods){
        createCustomMethod(customMethod.id, customMethod.header, customMethod.body);
    }
}

/*!
 * \brief Slot for modifying a custom method object stored in the model corresponding to the changed custom method widget.
 * 
 */
void ComponentWidget::methodChanged(){
    CustomMethodWidget* customMethod = qobject_cast<CustomMethodWidget*>(sender());
    model->modifyCustomMethod(this->id, customMethod->getID(), customMethod->getHeader(), customMethod->getBody());
}

/*!
 * \brief Slot for modifying the object name in the model correspondig to the changed object name widget.
 * 
 */
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

/*!
 * \brief Slot for modifying the item type in the model correspondig to the changed item type widget.
 * 
 */
void ComponentWidget::itemTypeChanged(){
    model->setItem(this->id,itemTypeLineEdit->text());
}

/*!
 * \brief Slot for modifying the data in the model correspondig to the changed text widget.
 * 
 */
void ComponentWidget::popUpTextChanged(){
    PopUpTextEdit* popUpTextEdit = qobject_cast<PopUpTextEdit*>(sender());
    model->setMethod(this->id,popUpTextEdit->getMethodType(),popUpTextEdit->toPlainText());
}

/*!
 * \brief Slot for modifying the constructor parameters stored in the model correspondig to the changed constructor parameters widget.
 * 
 */
void ComponentWidget::constructorParameterChanged(){
    QLineEdit* lineEdit = qobject_cast<QLineEdit*>(sender());
    model->setConstructorParameter(this->id,lineEdit->text());
}
