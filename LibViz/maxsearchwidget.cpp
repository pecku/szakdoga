#include "maxsearchwidget.h"

MaxSearchWidget::MaxSearchWidget(QString name, QWidget *parent) : ProcedureWidget(parent)
{
    setParentClass("MaxSearch");
    setName(name);

    gridlayout = new QGridLayout();

    valueLabel = new QLabel("Value:");
    valueLineEdit = new QLineEdit();
    gridlayout->addWidget(valueLabel,0,0);
    gridlayout->addWidget(valueLineEdit,0,1);

    compareLabel = new QLabel("Compare:");
    greaterRadioButton = new QRadioButton("Greater");
    greaterRadioButton->setChecked(true);
    lessRadioButton = new QRadioButton("Less");
    QHBoxLayout* compareLayout = new QHBoxLayout();
    compareLayout->addWidget(greaterRadioButton);
    compareLayout->addWidget(lessRadioButton);
    compareLayout->addSpacerItem(new QSpacerItem(maximumWidth(),0,QSizePolicy::Maximum));
    gridlayout->addWidget(compareLabel,1,0);
    gridlayout->addLayout(compareLayout,1,1);

    funcLabel = new QLabel("Func:");
    funcTextEdit = new QTextEdit();
    gridlayout->addWidget(funcLabel,2,0);
    gridlayout->addWidget(funcTextEdit,2,1);

    condLabel = new QLabel("Condition:");
    condTextEdit = new QTextEdit();
    gridlayout->addWidget(condLabel,3,0);
    gridlayout->addWidget(condTextEdit,3,1);

    firstLabel = new QLabel("First:");
    firstTextEdit = new QTextEdit();
    gridlayout->addWidget(firstLabel,4,0);
    gridlayout->addWidget(firstTextEdit,4,1);

    whileCondLabel = new QLabel("While Condition:");
    whileCondTextEdit = new QTextEdit();
    gridlayout->addWidget(whileCondLabel,5,0);
    gridlayout->addWidget(whileCondTextEdit,5,1);

    vboxlayout->addLayout(gridlayout);
}
