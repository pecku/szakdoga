#include "procedurewidget.h"

ProcedureWidget::ProcedureWidget(QString name, ProcedureType type, QWidget *parent) : QWidget(parent)
{
    vboxlayout = new QVBoxLayout(this);
    vboxlayout->setAlignment(Qt::Alignment(Qt::AlignmentFlag::AlignTop));

    memberLayout = new QVBoxLayout();

    this->name = name;
    nameLabel = new QLabel(name);
    parentClassLabel = new QLabel(procedureTypeNameStrings[type]);
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

    enorLabel = new QLabel("Enumerator:");
    enorComboBox = new QComboBox();
    gridlayout->addWidget(enorLabel,1,0);
    gridlayout->addWidget(enorComboBox,1,1);

    optimistLabel = nullptr;
    optimistCheckBox = nullptr;
    valueLabel = nullptr;
    valueLineEdit = nullptr;
    compareLabel = nullptr;
    greaterRadioButton = nullptr;
    lessRadioButton = nullptr;
    funcLabel = nullptr;
    funcTextEdit = nullptr;
    neutralLabel = nullptr;
    neutralTextEdit = nullptr;
    addLabel = nullptr;
    addTextEdit = nullptr;

    if(type == LINSEARCH){
        optimistLabel = new QLabel("Optimist:");
        optimistCheckBox = new QCheckBox();
        gridlayout->addWidget(optimistLabel,2,0);
        gridlayout->addWidget(optimistCheckBox,2,1);
    }

    if(type == MAXSEARCH || type == SUMMATION){
        valueLabel = new QLabel("Value:");
        valueLineEdit = new QLineEdit();
        gridlayout->addWidget(valueLabel,3,0);
        gridlayout->addWidget(valueLineEdit,3,1);
    }

    if(type == MAXSEARCH){
        compareLabel = new QLabel("Compare:");
        greaterRadioButton = new QRadioButton("Greater");
        greaterRadioButton->setChecked(true);
        lessRadioButton = new QRadioButton("Less");
        QHBoxLayout* compareLayout = new QHBoxLayout();
        compareLayout->addWidget(greaterRadioButton);
        compareLayout->addWidget(lessRadioButton);
        compareLayout->addSpacerItem(new QSpacerItem(maximumWidth(),0,QSizePolicy::Maximum));
        gridlayout->addWidget(compareLabel,4,0);
        gridlayout->addLayout(compareLayout,4,1);
    }

    if(type == MAXSEARCH || type == SUMMATION){
        funcLabel = new QLabel("Func:");
        funcTextEdit = new QTextEdit();
        gridlayout->addWidget(funcLabel,5,0);
        gridlayout->addWidget(funcTextEdit,5,1);
    }

    if(type == SUMMATION){
        neutralLabel = new QLabel("Neutral:");
        neutralTextEdit = new QTextEdit();
        gridlayout->addWidget(neutralLabel,6,0);
        gridlayout->addWidget(neutralTextEdit,6,1);

        addLabel = new QLabel("Add:");
        addTextEdit = new QTextEdit();
        gridlayout->addWidget(addLabel,7,0);
        gridlayout->addWidget(addTextEdit,7,1);
    }

    condLabel = new QLabel("Condition:");
    condTextEdit = new QTextEdit();
    gridlayout->addWidget(condLabel,8,0);
    gridlayout->addWidget(condTextEdit,8,1);

    firstLabel = new QLabel("First:");
    firstTextEdit = new QTextEdit();
    gridlayout->addWidget(firstLabel,9,0);
    gridlayout->addWidget(firstTextEdit,9,1);

    whileCondLabel = new QLabel("While Condition:");
    whileCondTextEdit = new QTextEdit();
    gridlayout->addWidget(whileCondLabel,10,0);
    gridlayout->addWidget(whileCondTextEdit,10,1);

    destructorLabel = new QLabel("Destructor:");
    destructorTextEdit = new QTextEdit();
    gridlayout->addWidget(destructorLabel,11,0);
    gridlayout->addWidget(destructorTextEdit,11,1);

    vboxlayout->addLayout(gridlayout);
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

QMap<Method,QString> ProcedureWidget::getData(){
    QMap<Method,QString> map;
    map.insert(DESTRUCTOR,destructorTextEdit->toPlainText());
    if(neutralTextEdit != nullptr)
        map.insert(NEUTRAL,neutralTextEdit->toPlainText());
    if(addTextEdit != nullptr)
        map.insert(ADD,addTextEdit->toPlainText());
    if(funcTextEdit != nullptr)
        map.insert(FUNC,funcTextEdit->toPlainText());
    map.insert(COND,condTextEdit->toPlainText());
    map.insert(FIRST,firstTextEdit->toPlainText());
    map.insert(WHILECOND,whileCondTextEdit->toPlainText());
    return map;
}
