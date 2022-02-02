#include "enumeratorwidget.h"

EnumeratorWidget::EnumeratorWidget(int id, QString name, ComponentType type, Model* model, QWidget *parent)
    : ComponentWidget(id,name,type,model,parent)
{
    initSegments();
}

void EnumeratorWidget::initSegments(){
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
        firstTextEdit = new PopUpTextEdit(FIRST);
        gridlayout->addWidget(firstLabel,1,0);
        gridlayout->addWidget(firstTextEdit,1,1);

        connect(firstTextEdit,SIGNAL(textChanged()),this,SLOT(popUpTextChanged()));

        nextLabel = new QLabel("Next:");
        nextTextEdit = new PopUpTextEdit(NEXT);
        gridlayout->addWidget(nextLabel,2,0);
        gridlayout->addWidget(nextTextEdit,2,1);

        connect(nextTextEdit,SIGNAL(textChanged()),this,SLOT(popUpTextChanged()));

        endLabel = new QLabel("End:");
        endTextEdit = new PopUpTextEdit(END);
        gridlayout->addWidget(endLabel,3,0);
        gridlayout->addWidget(endTextEdit,3,1);

        connect(endTextEdit,SIGNAL(textChanged()),this,SLOT(popUpTextChanged()));

        currentLabel = new QLabel("Current:");
        currentTextEdit = new PopUpTextEdit(CURRENT);
        gridlayout->addWidget(currentLabel,4,0);
        gridlayout->addWidget(currentTextEdit,4,1);

        connect(currentTextEdit,SIGNAL(textChanged()),this,SLOT(popUpTextChanged()));
    }
}
