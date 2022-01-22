#include "linsearchwidget.h"

LinSearchWidget::LinSearchWidget(QString name, QWidget *parent) : ProcedureWidget(parent)
{
    setParentClass("LinSearch");
    setName(name);

    gridlayout = new QGridLayout();

    optimistLabel = new QLabel("Optimist:");
    optimistCheckBox = new QCheckBox();
    gridlayout->addWidget(optimistLabel,0,0);
    gridlayout->addWidget(optimistCheckBox,0,1);

    condLabel = new QLabel("Condition:");
    condTextEdit = new QTextEdit();
    gridlayout->addWidget(condLabel,1,0);
    gridlayout->addWidget(condTextEdit,1,1);

    firstLabel = new QLabel("First:");
    firstTextEdit = new QTextEdit();
    gridlayout->addWidget(firstLabel,2,0);
    gridlayout->addWidget(firstTextEdit,2,1);

    whileCondLabel = new QLabel("While Condition:");
    whileCondTextEdit = new QTextEdit();
    gridlayout->addWidget(whileCondLabel,3,0);
    gridlayout->addWidget(whileCondTextEdit,3,1);

    vboxlayout->addLayout(gridlayout);
}
