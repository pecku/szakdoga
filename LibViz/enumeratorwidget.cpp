#include "enumeratorwidget.h"

EnumeratorWidget::EnumeratorWidget(int id, QString name, ComponentType type, Model* model, QWidget *parent)
    : ComponentWidget(id,name,type,model,parent)
{
    initSegments();
}

EnumeratorWidget::EnumeratorWidget(const Component& component, Model* model, QWidget *parent) : EnumeratorWidget(component.getID(),component.getName(),component.getType(),model,parent)
{

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
        gridlayout->addWidget(firstLabel,2,0);
        gridlayout->addWidget(firstTextEdit,2,1);

        connect(firstTextEdit,SIGNAL(textChanged()),this,SLOT(popUpTextChanged()));

        nextLabel = new QLabel("Next:");
        nextTextEdit = new PopUpTextEdit(NEXT);
        gridlayout->addWidget(nextLabel,3,0);
        gridlayout->addWidget(nextTextEdit,3,1);

        connect(nextTextEdit,SIGNAL(textChanged()),this,SLOT(popUpTextChanged()));

        endLabel = new QLabel("End:");
        endTextEdit = new PopUpTextEdit(END);
        gridlayout->addWidget(endLabel,4,0);
        gridlayout->addWidget(endTextEdit,4,1);

        connect(endTextEdit,SIGNAL(textChanged()),this,SLOT(popUpTextChanged()));

        currentLabel = new QLabel("Current:");
        currentTextEdit = new PopUpTextEdit(CURRENT);
        gridlayout->addWidget(currentLabel,5,0);
        gridlayout->addWidget(currentTextEdit,5,1);

        connect(currentTextEdit,SIGNAL(textChanged()),this,SLOT(popUpTextChanged()));
    }
}

bool EnumeratorWidget::checkRequired(){
    bool allgood = checkRequiredBase();
    if(type == DEFAULT){
        firstTextEdit->setStyleSheet("");
        nextTextEdit->setStyleSheet("");
        endTextEdit->setStyleSheet("");
        currentTextEdit->setStyleSheet("");

        if(firstTextEdit->toPlainText() == ""){
            firstTextEdit->setStyleSheet("border:2px solid red;");
            allgood = false;
        }
        if(nextTextEdit->toPlainText() == ""){
            nextTextEdit->setStyleSheet("border:2px solid red;");
            allgood = false;
        }
        if(endTextEdit->toPlainText() == ""){
            endTextEdit->setStyleSheet("border:2px solid red;");
            allgood = false;
        }
        if(currentTextEdit->toPlainText() == ""){
            currentTextEdit->setStyleSheet("border:2px solid red;");
            allgood = false;
        }
    }

    return allgood;
}
