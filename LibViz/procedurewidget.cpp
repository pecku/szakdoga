#include "procedurewidget.h"

ProcedureWidget::ProcedureWidget(QWidget *parent) : QWidget(parent)
{
    vboxlayout = new QVBoxLayout(this);
    vboxlayout->setAlignment(Qt::Alignment(Qt::AlignmentFlag::AlignTop));

    memberLayout = new QVBoxLayout();

    nameLabel = new QLabel("Name");
    parentClassLabel = new QLabel("Procedure");
    QHBoxLayout* nameLayout = new QHBoxLayout();
    nameLayout->addWidget(nameLabel);
    nameLayout->addSpacerItem(new QSpacerItem(maximumWidth(),0,QSizePolicy::Maximum));
    nameLayout->addWidget(parentClassLabel);

    vboxlayout->addLayout(nameLayout);

    QPushButton* addnewmemberbutton = new QPushButton("Add new private member");
    connect(addnewmemberbutton,SIGNAL(clicked()),this,SLOT(onAddNewMemberClicked()));
    vboxlayout->addWidget(addnewmemberbutton);

    vboxlayout->addLayout(memberLayout);
}

void ProcedureWidget::onAddNewMemberClicked(){
    MemberWidget* member = new MemberWidget();
    memberLayout->addWidget(member);
    members.push_back(member);
}

QMap<QString,QString> ProcedureWidget::getMembers(){
    QMap<QString,QString> map;
    for(MemberWidget* member : members){
        map.insert(member->getType(),member->getName());
    }
    return map;
}
