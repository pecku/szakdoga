#include "selectionwidget.h"

SelectionWidget::SelectionWidget(QString name, QWidget *parent) : ProcedureWidget(parent)
{
    setParentClass("Selection");
    setName(name);

    gridlayout = new QGridLayout();

    itemTypeLabel = new QLabel("Item type:");
    itemTypeLineEdit = new QLineEdit();
    gridlayout->addWidget(itemTypeLabel,0,0);
    gridlayout->addWidget(itemTypeLineEdit,0,1);

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

    destructorLabel = new QLabel("Destructor:");
    destructorTextEdit = new QTextEdit();
    gridlayout->addWidget(destructorLabel,4,0);
    gridlayout->addWidget(destructorTextEdit,4,1);

    enorLabel = new QLabel("Enumerator:");
    enorComboBox = new QComboBox();
    gridlayout->addWidget(enorLabel,5,0);
    gridlayout->addWidget(enorComboBox,5,1);

    vboxlayout->addLayout(gridlayout);
}
