#include "enumeratorwidget.h"

EnumeratorWidget::EnumeratorWidget(QString name, EnumeratorType type, QWidget *parent) : QWidget(parent)
{
    this->type = type;

    vboxlayout = new QVBoxLayout(this);
    vboxlayout->setAlignment(Qt::Alignment(Qt::AlignmentFlag::AlignTop));

    memberLayout = new QVBoxLayout();

    this->name = name;
    nameLabel = new QLabel(name);
    parentClassLabel = new QLabel(enumeratorTypeNameStrings[type]);
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

    firstLabel = nullptr;
    firstTextEdit = nullptr;
    nextLabel = nullptr;
    nextTextEdit = nullptr;
    endLabel = nullptr;
    endTextEdit = nullptr;
    currentLabel = nullptr;
    currentTextEdit = nullptr;

    if(type != SEQINFILE){
        firstLabel = new QLabel("First:");
        firstTextEdit = new QTextEdit();
        gridlayout->addWidget(firstLabel,1,0);
        gridlayout->addWidget(firstTextEdit,1,1);

        nextLabel = new QLabel("Next:");
        nextTextEdit = new QTextEdit();
        gridlayout->addWidget(nextLabel,2,0);
        gridlayout->addWidget(nextTextEdit,2,1);

        endLabel = new QLabel("End:");
        endTextEdit = new QTextEdit();
        gridlayout->addWidget(endLabel,3,0);
        gridlayout->addWidget(endTextEdit,3,1);

        currentLabel = new QLabel("Current:");
        currentTextEdit = new QTextEdit();
        gridlayout->addWidget(currentLabel,4,0);
        gridlayout->addWidget(currentTextEdit,4,1);
    }

    destructorLabel = new QLabel("Destructor:");
    destructorTextEdit = new QTextEdit();
    gridlayout->addWidget(destructorLabel,5,0);
    gridlayout->addWidget(destructorTextEdit,5,1);

    vboxlayout->addLayout(gridlayout);
}

void EnumeratorWidget::onAddNewMemberClicked(){
    MemberWidget* member = new MemberWidget();
    memberLayout->addWidget(member);
    members.push_back(member);
}

QMap<QString,QString> EnumeratorWidget::getMembers(){
    QMap<QString,QString> map;
    for(MemberWidget* member : members){
        map.insert(member->getType(),member->getName());
    }
    return map;
}

QMap<Method,QString> EnumeratorWidget::getData(){
    QMap<Method,QString> map;
    map.insert(DESTRUCTOR,destructorTextEdit->toPlainText());
    if(firstTextEdit != nullptr)
        map.insert(FIRST,firstTextEdit->toPlainText());
    if(nextTextEdit != nullptr)
        map.insert(NEXT,nextTextEdit->toPlainText());
    if(endTextEdit != nullptr)
        map.insert(END,endTextEdit->toPlainText());
    if(currentTextEdit != nullptr)
        map.insert(CURRENT,currentTextEdit->toPlainText());
    return map;
}
