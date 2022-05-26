#include "structwidget.h"

/*!
 * \brief Constructs a new Struct Widget object.
 * 
 * \param id The id of the struct.
 * \param name The name of the struct.
 * \param model The model that stores the struct.
 * \param parent The parent widget.
 */
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

/*!
 * \brief Constructs a new Struct Widget from the object stored in the model.
 * 
 * \param _struct The struct object that contains the data.
 * \param model The model that stores the struct.
 * \param parent The parent widget.
 */
StructWidget::StructWidget(const Struct& _struct, Model* model, QWidget *parent) : StructWidget(_struct.getID(), _struct.getName(), model, parent)
{
    createMembers(_struct.getMembers());
    createCustomMethods(_struct.getCustomMethods());
}

/*!
 * \brief Slot for when the 'Add new private member' button is clicked.
 * 
 */
void StructWidget::onAddNewMemberClicked(){
    createMember(model->createMember(this->id));
}

/*!
 * \brief Creates a new member widget.
 * 
 * \param id The id of the member.
 * \param type The type of the member.
 * \param name The name of the member.
 */
void StructWidget::createMember(int id, QString type, QString name){
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
void StructWidget::deleteMember(){
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
void StructWidget::memberChanged(){
    MemberWidget* member = qobject_cast<MemberWidget*>(sender());
    model->modifyMember(this->id, member->getID(), member->getType(), member->getName());
}

/*!
 * \brief Slot for when the 'Add new method' button is clicked.
 * 
 */
void StructWidget::onAddNewMethodClicked(){
    createCustomMethod(model->createCustomMethod(this->id));
}

/*!
 * \brief Creates a new custom method widget.
 * 
 * \param id The id of the custom method.
 * \param header The header of the custom method.
 * \param body The body of the custom method.
 */
void StructWidget::createCustomMethod(int id, QString header, QString body){
    CustomMethodWidget* customMethod = new CustomMethodWidget(id, header, body);
    customMethodLayout->addWidget(customMethod);
    customMethods.push_back(customMethod);
    connect(customMethod,SIGNAL(edited()),this,SLOT(methodChanged()));
    connect(customMethod,SIGNAL(deleteMe()),this,SLOT(deleteMethod()));
}

/*!
 * \brief Creates member widgets from a map of ids and member objects.
 * 
 * \param members Map of ids and member objects.
 */
void StructWidget::createMembers(QMap<int, Member> members){
    foreach(Member member, members){
        createMember(member.id, member.type, member.name);
    }
}

/*!
 * \brief Creates custom method widgets from a map of ids and custom method objects.
 * 
 * \param customMethods Map of ids and custom method objects.
 */
void StructWidget::createCustomMethods(QMap<int, CustomMethod> customMethods){
    foreach(CustomMethod customMethod, customMethods){
        createCustomMethod(customMethod.id, customMethod.header, customMethod.body);
    }
}

/*!
 * \brief Deletes the custom method widget which the signal came from.
 * 
 */
void StructWidget::deleteMethod(){
    CustomMethodWidget* customMethod = qobject_cast<CustomMethodWidget*>(sender());
    customMethods.removeAll(customMethod);
    customMethodLayout->removeWidget(customMethod);
    model->deleteCustomMethod(this->id, customMethod->getID());
    delete customMethod;
}

/*!
 * \brief Slot for modifying a custom method object stored in the model corresponding to the changed custom method widget.
 * 
 */
void StructWidget::methodChanged(){
    CustomMethodWidget* customMethod = qobject_cast<CustomMethodWidget*>(sender());
    model->modifyCustomMethod(this->id, customMethod->getID(), customMethod->getHeader(), customMethod->getBody());
}
