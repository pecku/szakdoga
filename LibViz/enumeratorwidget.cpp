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
    if(constructorParameterLineEdit != nullptr) constructorParameterLineEdit->setText(component.getConstructorParameter());
    if(firstTextEdit != nullptr) firstTextEdit->setText(methods[FIRST]);
    if(nextTextEdit != nullptr) nextTextEdit->setText(methods[NEXT]);
    if(endTextEdit != nullptr) endTextEdit->setText(methods[END]);
    if(currentTextEdit != nullptr) currentTextEdit->setText(methods[CURRENT]);
    if(destructorTextEdit != nullptr) destructorTextEdit->setText(methods[DESTRUCTOR]);

    createMembers(component.getMembers());
    createCustomMethods(component.getCustomMethods());

    connectSignals();
}

void EnumeratorWidget::initSegments(){
    int gridlayoutIndex = 2;

    constructorParameterLabel = nullptr;
    constructorParameterLineEdit = nullptr;
    firstLabel = nullptr;
    firstTextEdit = nullptr;
    nextLabel = nullptr;
    nextTextEdit = nullptr;
    endLabel = nullptr;
    endTextEdit = nullptr;
    currentLabel = nullptr;
    currentTextEdit = nullptr;


    if(type != DEFAULT){
        constructorParameterLabel = new QLabel("Constructor parameter:");
        constructorParameterLineEdit = new QLineEdit();
        gridlayout->addWidget(constructorParameterLabel,gridlayoutIndex,0);
        gridlayout->addWidget(constructorParameterLineEdit,gridlayoutIndex,1);
    }

    if(type != SEQINFILE){
        firstLabel = new QLabel("First:");
        firstTextEdit = new PopUpTextEdit(FIRST);
        gridlayout->addWidget(firstLabel,++gridlayoutIndex,0);
        gridlayout->addWidget(firstTextEdit,gridlayoutIndex,1);

        nextLabel = new QLabel("Next:");
        nextTextEdit = new PopUpTextEdit(NEXT);
        gridlayout->addWidget(nextLabel,++gridlayoutIndex,0);
        gridlayout->addWidget(nextTextEdit,gridlayoutIndex,1);

        endLabel = new QLabel("End:");
        endTextEdit = new PopUpTextEdit(END);
        gridlayout->addWidget(endLabel,++gridlayoutIndex,0);
        gridlayout->addWidget(endTextEdit,gridlayoutIndex,1);

        currentLabel = new QLabel("Current:");
        currentTextEdit = new PopUpTextEdit(CURRENT);
        gridlayout->addWidget(currentLabel,++gridlayoutIndex,0);
        gridlayout->addWidget(currentTextEdit,gridlayoutIndex,1);
    }
}

void EnumeratorWidget::connectSignals(){
    if(constructorParameterLineEdit != nullptr) connect(constructorParameterLineEdit,SIGNAL(editingFinished()),this,SLOT(constructorParameterChanged()));
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
