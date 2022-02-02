#include "procedurewidget.h"

ProcedureWidget::ProcedureWidget(int id, QString name, ComponentType type, Model* model, QWidget *parent)
    :  ComponentWidget(id,name,type,model,parent)
{
    initSegments();
}

void ProcedureWidget::initSegments(){
    enorLabel = new QLabel("Enumerator:");
    enorComboBox = new QComboBox();
    enorComboBox->setPlaceholderText("No enumerator");
    enorComboBox->setCurrentIndex(-1);
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

        connect(optimistCheckBox,SIGNAL(stateChanged(int)),this,SLOT(optimistChanged()));
    }

    if(type == MAXSEARCH || type == SUMMATION){
        valueLabel = new QLabel("Value:");
        valueLineEdit = new QLineEdit();
        gridlayout->addWidget(valueLabel,3,0);
        gridlayout->addWidget(valueLineEdit,3,1);

        connect(valueLineEdit,SIGNAL(editingFinished()),this,SLOT(valueChanged()));
    }

    if(type == MAXSEARCH){
        compareLabel = new QLabel("Compare:");
        greaterRadioButton = new QRadioButton("Greater");
        lessRadioButton = new QRadioButton("Less");
        QHBoxLayout* compareLayout = new QHBoxLayout();
        compareLayout->addWidget(greaterRadioButton);
        compareLayout->addWidget(lessRadioButton);
        compareLayout->addSpacerItem(new QSpacerItem(maximumWidth(),0,QSizePolicy::Maximum));
        gridlayout->addWidget(compareLabel,4,0);
        gridlayout->addLayout(compareLayout,4,1);

        connect(greaterRadioButton,SIGNAL(toggled(bool)),this,SLOT(compareChanged()));
        greaterRadioButton->setChecked(true);
    }

    if(type == MAXSEARCH || type == SUMMATION){
        funcLabel = new QLabel("Func:");
        funcTextEdit = new PopUpTextEdit(FUNC);
        gridlayout->addWidget(funcLabel,5,0);
        gridlayout->addWidget(funcTextEdit,5,1);

        connect(funcTextEdit,SIGNAL(textChanged()),this,SLOT(popUpTextChanged()));
    }

    if(type == SUMMATION){
        neutralLabel = new QLabel("Neutral:");
        neutralTextEdit = new PopUpTextEdit(NEUTRAL);
        gridlayout->addWidget(neutralLabel,6,0);
        gridlayout->addWidget(neutralTextEdit,6,1);

        connect(neutralTextEdit,SIGNAL(textChanged()),this,SLOT(popUpTextChanged()));

        addLabel = new QLabel("Add:");
        addTextEdit = new PopUpTextEdit(ADD);
        gridlayout->addWidget(addLabel,7,0);
        gridlayout->addWidget(addTextEdit,7,1);

        connect(addTextEdit,SIGNAL(textChanged()),this,SLOT(popUpTextChanged()));
    }

    condLabel = new QLabel("Condition:");
    condTextEdit = new PopUpTextEdit(COND);
    gridlayout->addWidget(condLabel,8,0);
    gridlayout->addWidget(condTextEdit,8,1);

    connect(condTextEdit,SIGNAL(textChanged()),this,SLOT(popUpTextChanged()));

    firstLabel = new QLabel("First:");
    firstTextEdit = new PopUpTextEdit(FIRST);
    gridlayout->addWidget(firstLabel,9,0);
    gridlayout->addWidget(firstTextEdit,9,1);

    connect(firstTextEdit,SIGNAL(textChanged()),this,SLOT(popUpTextChanged()));

    whileCondLabel = new QLabel("While Condition:");
    whileCondTextEdit = new PopUpTextEdit(WHILECOND);
    gridlayout->addWidget(whileCondLabel,10,0);
    gridlayout->addWidget(whileCondTextEdit,10,1);

    connect(whileCondTextEdit,SIGNAL(textChanged()),this,SLOT(popUpTextChanged()));
}

void ProcedureWidget::optimistChanged(){
    model->setOptimist(this->id,qobject_cast<QCheckBox*>(sender())->isChecked());
}

void ProcedureWidget::valueChanged(){
    model->setValue(this->id,qobject_cast<QLineEdit*>(sender())->text());
}

void ProcedureWidget::compareChanged(){
    model->setCompare(this->id,qobject_cast<QRadioButton*>(sender())->isChecked()?"Greater":"Less");
}

void ProcedureWidget::addEnumeratorChoice(QString enumeratorName){
    enorComboBox->addItem(enumeratorName);
}
