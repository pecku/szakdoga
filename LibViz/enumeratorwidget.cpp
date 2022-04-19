#include "enumeratorwidget.h"

EnumeratorWidget::EnumeratorWidget(int id, QString name, ComponentType type, Model* model, QWidget *parent)
    : ComponentWidget(id,name,type,model,parent)
{
    initSegments();
    connectSignals();
}

EnumeratorWidget::EnumeratorWidget(const Component& component, Model* model, QWidget *parent) : ComponentWidget(component.getID(),component.getName(),component.getType(),model,parent)
{
    initSegments();

    QMap<MethodType,QString> methods = component.getMethods();
    objectNameLineEdit->setText(component.getObjectName());
    itemTypeLineEdit->setText(component.getItem());
    if(firstTextEdit != nullptr) firstTextEdit->setText(methods[FIRST]);
    if(nextTextEdit != nullptr) nextTextEdit->setText(methods[NEXT]);
    if(endTextEdit != nullptr) endTextEdit->setText(methods[END]);
    if(currentTextEdit != nullptr) currentTextEdit->setText(methods[CURRENT]);
    if(destructorTextEdit != nullptr) destructorTextEdit->setText(methods[DESTRUCTOR]);

    connectSignals();
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

        nextLabel = new QLabel("Next:");
        nextTextEdit = new PopUpTextEdit(NEXT);
        gridlayout->addWidget(nextLabel,3,0);
        gridlayout->addWidget(nextTextEdit,3,1);

        endLabel = new QLabel("End:");
        endTextEdit = new PopUpTextEdit(END);
        gridlayout->addWidget(endLabel,4,0);
        gridlayout->addWidget(endTextEdit,4,1);

        currentLabel = new QLabel("Current:");
        currentTextEdit = new PopUpTextEdit(CURRENT);
        gridlayout->addWidget(currentLabel,5,0);
        gridlayout->addWidget(currentTextEdit,5,1);
    }
}

void EnumeratorWidget::connectSignals(){
    if(firstTextEdit != nullptr) connect(firstTextEdit,SIGNAL(textChanged()),this,SLOT(popUpTextChanged()));
    if(nextTextEdit != nullptr) connect(nextTextEdit,SIGNAL(textChanged()),this,SLOT(popUpTextChanged()));
    if(endTextEdit != nullptr) connect(endTextEdit,SIGNAL(textChanged()),this,SLOT(popUpTextChanged()));
    if(currentTextEdit != nullptr) connect(currentTextEdit,SIGNAL(textChanged()),this,SLOT(popUpTextChanged()));

    ComponentWidget::connectSignals();
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
