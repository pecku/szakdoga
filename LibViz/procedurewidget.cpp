#include "procedurewidget.h"

/*!
 * \brief Constructs a new Procedure Widget object.
 * 
 * \param id The id of the procedure.
 * \param name The name of the procedure.
 * \param type The type of the procedure.
 * \param model The model that stores the procedure.
 * \param parent The parent widget.
 */
ProcedureWidget::ProcedureWidget(int id, QString name, ComponentType type, Model* model, QWidget *parent)
    :  ComponentWidget(id,name,type,model,parent)
{
    initSegments();
    connectSignals();
}

/*!
 * \brief Constructs a new Procedure Widget object from the object stored in the model.
 * 
 * \param component The object that stores the data.
 * \param model The model that stores the procedure.
 * \param parent The parent widget.
 */
ProcedureWidget::ProcedureWidget(const Component& component, Model* model, QWidget *parent) : ComponentWidget(component.getID(),component.getName(),component.getType(),model,parent)
{
    initSegments();

    QMap<MethodType,QString> methods = component.getMethods();

    QString enumeratorName = model->getEnumeratorNameById(component.getEnumeratorID());
    if(enumeratorName != nullptr){
        enorComboBox->addItem(enumeratorName,component.getEnumeratorID());
        enorComboBox->setCurrentText(enumeratorName);
    }
    objectNameLineEdit->setText(component.getObjectName());
    itemTypeLineEdit->setText(component.getItem());
    constructorParameterLineEdit->setText(component.getConstructorParameter());
    useInMainCheckBox->setChecked(component.getUseInMain());
    if(optimistCheckBox != nullptr) optimistCheckBox->setChecked(component.getOptimist());
    if(valueLineEdit != nullptr) valueLineEdit->setText(component.getValue());
    if(greaterRadioButton != nullptr) greaterRadioButton->setChecked(component.getCompare() == "Greater");
    if(lessRadioButton != nullptr) lessRadioButton->setChecked(component.getCompare() == "Less");
    if(neutralTextEdit != nullptr) neutralTextEdit->setText(methods[NEUTRAL]);
    if(addTextEdit != nullptr) addTextEdit->setText(methods[ADD]);
    if(funcTextEdit != nullptr) funcTextEdit->setText(methods[FUNC]);
    if(condTextEdit != nullptr) condTextEdit->setText(methods[COND]);
    if(firstTextEdit != nullptr) firstTextEdit->setText(methods[FIRST]);
    if(whileCondTextEdit != nullptr) whileCondTextEdit->setText(methods[WHILECOND]);
    if(destructorTextEdit != nullptr) destructorTextEdit->setText(methods[DESTRUCTOR]);

    createMembers(component.getMembers());
    createCustomMethods(component.getCustomMethods());

    connectSignals();
}

/*!
 * \brief Initialize the widgets of the procedure widget.
 * 
 */
void ProcedureWidget::initSegments(){
    int gridlayoutIndex = 3;

    useInMainLabel = new QLabel("Use in main:");
    useInMainCheckBox = new QCheckBox();
    useInMainCheckBox->setChecked(true);
    gridlayout->addWidget(useInMainLabel,gridlayoutIndex,0);
    gridlayout->addWidget(useInMainCheckBox,gridlayoutIndex,1);

    enorLabel = new QLabel("Enumerator:");
    enorComboBox = new QComboBox();
    enorComboBox->setPlaceholderText("No enumerator");
    enorComboBox->setCurrentIndex(-1);
    gridlayout->addWidget(enorLabel,++gridlayoutIndex,0);
    gridlayout->addWidget(enorComboBox,gridlayoutIndex,1);

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
        gridlayout->addWidget(optimistLabel,++gridlayoutIndex,0);
        gridlayout->addWidget(optimistCheckBox,gridlayoutIndex,1);
    }

    if(type == MAXSEARCH || type == SUMMATION){
        valueLabel = new QLabel("Value:");
        valueLineEdit = new QLineEdit();
        gridlayout->addWidget(valueLabel,++gridlayoutIndex,0);
        gridlayout->addWidget(valueLineEdit,gridlayoutIndex,1);
    }

    if(type == MAXSEARCH){
        compareLabel = new QLabel("Compare:");
        greaterRadioButton = new QRadioButton("Greater");
        lessRadioButton = new QRadioButton("Less");
        QHBoxLayout* compareLayout = new QHBoxLayout();
        compareLayout->addWidget(greaterRadioButton);
        compareLayout->addWidget(lessRadioButton);
        compareLayout->addSpacerItem(new QSpacerItem(maximumWidth(),0,QSizePolicy::Maximum));
        gridlayout->addWidget(compareLabel,++gridlayoutIndex,0);
        gridlayout->addLayout(compareLayout,gridlayoutIndex,1);
        greaterRadioButton->setChecked(true);
    }

    if(type == MAXSEARCH || type == SUMMATION){
        funcLabel = new QLabel("Func:");
        funcTextEdit = new PopUpTextEdit(FUNC);
        gridlayout->addWidget(funcLabel,++gridlayoutIndex,0);
        gridlayout->addWidget(funcTextEdit,gridlayoutIndex,1);
    }

    if(type == SUMMATION){
        neutralLabel = new QLabel("Neutral:");
        neutralTextEdit = new PopUpTextEdit(NEUTRAL);
        gridlayout->addWidget(neutralLabel,++gridlayoutIndex,0);
        gridlayout->addWidget(neutralTextEdit,gridlayoutIndex,1);

        addLabel = new QLabel("Add:");
        addTextEdit = new PopUpTextEdit(ADD);
        gridlayout->addWidget(addLabel,++gridlayoutIndex,0);
        gridlayout->addWidget(addTextEdit,gridlayoutIndex,1);
    }

    condLabel = new QLabel("Condition:");
    condTextEdit = new PopUpTextEdit(COND);
    gridlayout->addWidget(condLabel,++gridlayoutIndex,0);
    gridlayout->addWidget(condTextEdit,gridlayoutIndex,1);

    firstLabel = new QLabel("First:");
    firstTextEdit = new PopUpTextEdit(FIRST);
    gridlayout->addWidget(firstLabel,++gridlayoutIndex,0);
    gridlayout->addWidget(firstTextEdit,gridlayoutIndex,1);

    whileCondLabel = new QLabel("While Condition:");
    whileCondTextEdit = new PopUpTextEdit(WHILECOND);
    gridlayout->addWidget(whileCondLabel,++gridlayoutIndex,0);
    gridlayout->addWidget(whileCondTextEdit,gridlayoutIndex,1);
}

/*!
 * \brief Connect the signals of the widget's members to the correct slots.
 * 
 */
void ProcedureWidget::connectSignals(){
    connect(useInMainCheckBox,SIGNAL(stateChanged(int)),this,SLOT(useInMainChanged()));
    connect(enorComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(enorChanged(int)));
    if(optimistCheckBox != nullptr) connect(optimistCheckBox,SIGNAL(stateChanged(int)),this,SLOT(optimistChanged()));
    if(valueLineEdit != nullptr) connect(valueLineEdit,SIGNAL(editingFinished()),this,SLOT(valueChanged()));
    if(greaterRadioButton != nullptr) connect(greaterRadioButton,SIGNAL(toggled(bool)),this,SLOT(compareChanged()));
    if(neutralTextEdit != nullptr) connect(neutralTextEdit,SIGNAL(textChanged()),this,SLOT(popUpTextChanged()));
    if(addTextEdit != nullptr) connect(addTextEdit,SIGNAL(textChanged()),this,SLOT(popUpTextChanged()));
    if(funcTextEdit != nullptr) connect(funcTextEdit,SIGNAL(textChanged()),this,SLOT(popUpTextChanged()));
    if(condTextEdit != nullptr) connect(condTextEdit,SIGNAL(textChanged()),this,SLOT(popUpTextChanged()));
    if(firstTextEdit != nullptr) connect(firstTextEdit,SIGNAL(textChanged()),this,SLOT(popUpTextChanged()));
    if(whileCondTextEdit != nullptr) connect(whileCondTextEdit,SIGNAL(textChanged()),this,SLOT(popUpTextChanged()));

    ComponentWidget::connectSignals();
}

/*!
 * \brief Checks if the required fields are filled in.
 * 
 * \return true 
 * \return false 
 */
bool ProcedureWidget::checkRequired(){
    bool allgood = checkRequiredBase();
    enorComboBox->setStyleSheet("");
    if(enorComboBox->currentIndex() < 0){
        enorComboBox->setStyleSheet("border:2px solid red;");
        allgood = false;
    }
    if(valueLineEdit != nullptr ){
        valueLineEdit->setStyleSheet("");
        if(valueLineEdit->text() == ""){
            valueLineEdit->setStyleSheet("border:2px solid red;");
            allgood = false;
        }
    }
    if(neutralTextEdit != nullptr ){
        neutralTextEdit->setStyleSheet("");
        if(neutralTextEdit->toPlainText() == ""){
            neutralTextEdit->setStyleSheet("border:2px solid red;");
            allgood = false;
        }
    }
    if(addTextEdit != nullptr){
        addTextEdit->setStyleSheet("");
        if(addTextEdit->toPlainText() == ""){
            addTextEdit->setStyleSheet("border:2px solid red;");
            allgood = false;
        }
    }
    if(funcTextEdit != nullptr){
        funcTextEdit->setStyleSheet("");
        if(funcTextEdit->toPlainText() == ""){
            funcTextEdit->setStyleSheet("border:2px solid red;");
            allgood = false;
        }
    }
    if(condTextEdit != nullptr){
        condTextEdit->setStyleSheet("");
        if(type == LINSEARCH && condTextEdit->toPlainText() == ""){
            condTextEdit->setStyleSheet("border:2px solid red;");
            allgood = false;
        }
    }
    if(type == DEFAULT){
        firstTextEdit->setStyleSheet("");
        if(firstTextEdit->toPlainText() == ""){
            firstTextEdit->setStyleSheet("border:2px solid red;");
            allgood = false;
        }
    }

    return allgood;
}

/*!
 * \brief Slot for when the 'use in main' checkbox is changed.
 * 
 */
void ProcedureWidget::useInMainChanged(){
    bool checked = qobject_cast<QCheckBox*>(sender())->isChecked();
    model->setUseInMain(this->id,checked);
    if(checked){
        emit useInMainChecked(getName(),this->id);
    }else{
        emit useInMainUnchecked(this->id);
    }
}

/*!
 * \brief Slot for when the enumerator selection changes.
 * 
 */
void ProcedureWidget::enorChanged(int index){
    if(index < 0) return;
    model->setEnumerator(this->id,enorComboBox->itemData(index).toInt());
}

/*!
 * \brief Slot for when the 'optimist' checkbox is changed.
 * 
 */
void ProcedureWidget::optimistChanged(){
    model->setOptimist(this->id,qobject_cast<QCheckBox*>(sender())->isChecked());
}

/*!
 * \brief Slot for when the 'value' has been edited.
 * 
 */
void ProcedureWidget::valueChanged(){
    model->setValue(this->id,qobject_cast<QLineEdit*>(sender())->text());
}

/*!
 * \brief Slot for when the 'compare' type changed.
 * 
 */
void ProcedureWidget::compareChanged(){
    model->setCompare(this->id,qobject_cast<QRadioButton*>(sender())->isChecked()?"Greater":"Less");
}

/*!
 * \brief Adds a new enumerator choice to the enumerator combobox.
 * 
 */
void ProcedureWidget::addEnumeratorChoice(QString enumeratorName, int enumeratorID){
    if(enorComboBox->findText(enumeratorName) == -1){
        enorComboBox->addItem(enumeratorName,enumeratorID);
    }
}

/*!
 * \brief Removes an enumerator choice from the enumerator combobox.
 * 
 */
void ProcedureWidget::removeEnumeratorChoice(int enumeratorID){
    for(int i = 0; i < enorComboBox->count(); i++){
        if(enorComboBox->itemData(i).toInt() == enumeratorID){
            enorComboBox->removeItem(i);
            break;
        }
    }
}
