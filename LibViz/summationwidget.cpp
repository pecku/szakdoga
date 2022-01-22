#include "summationwidget.h"

SummationWidget::SummationWidget(QString name, QWidget *parent) : ProcedureWidget(parent)
{
    setParentClass("Summation");
    setName(name);

    gridlayout = new QGridLayout();

    valueLabel = new QLabel("Value:");
    valueLineEdit = new QLineEdit();
    gridlayout->addWidget(valueLabel,0,0);
    gridlayout->addWidget(valueLineEdit,0,1);

    neutralLabel = new QLabel("Neutral:");
    neutralTextEdit = new QTextEdit();
    gridlayout->addWidget(neutralLabel,1,0);
    gridlayout->addWidget(neutralTextEdit,1,1);

    addLabel = new QLabel("Add:");
    addTextEdit = new QTextEdit();
    gridlayout->addWidget(addLabel,2,0);
    gridlayout->addWidget(addTextEdit,2,1);

    funcLabel = new QLabel("Func:");
    funcTextEdit = new QTextEdit();
    gridlayout->addWidget(funcLabel,3,0);
    gridlayout->addWidget(funcTextEdit,3,1);

    condLabel = new QLabel("Condition:");
    condTextEdit = new QTextEdit();
    gridlayout->addWidget(condLabel,4,0);
    gridlayout->addWidget(condTextEdit,4,1);

    firstLabel = new QLabel("First:");
    firstTextEdit = new QTextEdit();
    gridlayout->addWidget(firstLabel,5,0);
    gridlayout->addWidget(firstTextEdit,5,1);

    whileCondLabel = new QLabel("While Condition:");
    whileCondTextEdit = new QTextEdit();
    gridlayout->addWidget(whileCondLabel,6,0);
    gridlayout->addWidget(whileCondTextEdit,6,1);

    vboxlayout->addLayout(gridlayout);
}
