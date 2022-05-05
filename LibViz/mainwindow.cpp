#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(1000,700);

    model = new Model();
    connect(model, SIGNAL(haveCompileOutput(QString)), this, SLOT(showCompileOutput(QString)));
    connect(model, SIGNAL(compileProcessEnded()), this, SLOT(allowCompile()));
    connect(model, SIGNAL(compilerPathNotSet()), this, SLOT(showCompilerPathWarning()));
    connect(model, SIGNAL(needProjectNameForSave()), this, SLOT(showProjectSaveDialog()));
    connect(model, SIGNAL(needProjectNameForOpen()), this, SLOT(showProjectOpenDialog()));
    connect(model, SIGNAL(wantToGenerateSource()), this, SLOT(generateSource()));
    connect(model, SIGNAL(projectLoaded(SaveData)), this, SLOT(refresh(SaveData)));
    connect(model, SIGNAL(cleared()), this, SLOT(clear()));

    centralSplitter = new QSplitter(Qt::Horizontal);
    centralSplitter->setContentsMargins(4,4,4,4);
    setCentralWidget(centralSplitter);

    initDialogs();
    initActions();
    initMenuBar();
    initComponentEditorSegment();
    initListSegment();
    initSourceSegment();
}

void MainWindow::createComponent(){
    QString name = createComponentDialog->getName();
    if(createComponentDialog->getComponent() == -1){
        int id = model->createStruct(name);
        StructWidget* structWidget = new StructWidget(id,name,model);
        toolBox->setCurrentIndex(toolBox->addItem(structWidget,name));
        structWidgets.push_back(structWidget);
    }else{
        ComponentType componentType = (ComponentType)createComponentDialog->getComponent().toInt();
        if(componentType == COUNTING || componentType == LINSEARCH || componentType == MAXSEARCH || componentType == SELECTION || componentType == SUMMATION){
            int id = model->createComponent(name, componentType);
            ProcedureWidget* procedure = new ProcedureWidget(id,name,componentType,model);
            connect(procedure,SIGNAL(useInMainChecked(QString,int)),this,SLOT(addListItem(QString,int)));
            connect(procedure,SIGNAL(useInMainUnchecked(int)),this,SLOT(deleteListItem(int)));
            toolBox->setCurrentIndex(toolBox->addItem(procedure,name));
            procedureWidgets.push_back(procedure);
            foreach(EnumeratorWidget* enorw, enumeratorWidgets){
                procedure->addEnumeratorChoice(enorw->getName(), enorw->getID());
            }
            addListItem(name,id);
        }else{
            int id = model->createComponent(name, componentType);
            EnumeratorWidget* enumerator = new EnumeratorWidget(id,name,componentType,model);
            toolBox->setCurrentIndex(toolBox->addItem(enumerator,name));
            enumeratorWidgets.push_back(enumerator);
            foreach(ProcedureWidget* procw, procedureWidgets){
                procw->addEnumeratorChoice(name, id);
            }
        }
    }
}

void MainWindow::deleteComponent(){
    ComponentWidget* component = qobject_cast<ComponentWidget*>(toolBox->currentWidget());
    if(component == nullptr){
        StructWidget* structWidget = qobject_cast<StructWidget*>(toolBox->currentWidget());
        if(structWidget == nullptr){
            return;
        }else{
            QMessageBox msg(QMessageBox::Icon::Question, "Delete Struct", "Sure you want to delete " + structWidget->getName() + "?", QMessageBox::Ok | QMessageBox::Cancel, this);
            msg.setDefaultButton(QMessageBox::Cancel);
            int msg_res = msg.exec();

            if(msg_res != QMessageBox::Ok) return;

            int id = structWidget->getID();
            toolBox->removeItem(toolBox->currentIndex());
            structWidgets.removeAll(structWidget);
            structWidgets.squeeze();
            model->deleteStruct(id);

            return;
        }
    }

    QMessageBox msg(QMessageBox::Icon::Question, "Delete Component", "Sure you want to delete " + component->getName() + "?", QMessageBox::Ok | QMessageBox::Cancel, this);
    msg.setDefaultButton(QMessageBox::Cancel);
    int msg_res = msg.exec();

    if(msg_res != QMessageBox::Ok) return;

    int id = component->getID();
    toolBox->removeItem(toolBox->currentIndex());
    procedureWidgets.removeAll(component);
    procedureWidgets.squeeze();
    enumeratorWidgets.removeAll(component);
    enumeratorWidgets.squeeze();
    model->deleteComponent(id);

    deleteListItem(id);

    ComponentType ct = component->getType();
    if(ct == DEFAULT || ct == ARRAY || ct == INTERVAL || ct == STRINGSTREAM || ct == SEQINFILE){
        foreach(ProcedureWidget* pw, procedureWidgets){
            pw->removeEnumeratorChoice(id);
        }
    }
}

void MainWindow::addListItem(QString componentName, int componentID){
    QListWidgetItem* listItem = new QListWidgetItem(componentName,listWidget,componentID);
    listItem->setData(Qt::UserRole,"component");
}

void MainWindow::deleteListItem(int id){
    listWidget->clearSelection();
    QListWidgetItem* item = nullptr;
    for(int i = 0; i < listWidget->count(); i++){
        if(listWidget->item(i)->type() == id){
            item = listWidget->item(i);
            break;
        }
    }
    listWidget->takeItem(listWidget->row(item));
}

void MainWindow::deleteListItem(){
    if(listWidget->currentItem() == nullptr) return;
    QListWidgetItem* currentItem = listWidget->currentItem();
    if(currentItem->data(Qt::UserRole).toString() == "component"){
        deleteComponent();
    }else{
        QMessageBox msg(QMessageBox::Icon::Question, "Delete Code Block", "Sure you want to delete the selected code block?", QMessageBox::Ok | QMessageBox::Cancel, this);
        msg.setDefaultButton(QMessageBox::Cancel);
        int msg_res = msg.exec();

        if(msg_res != QMessageBox::Ok) return;

        model->deleteCodeBlock(listWidget->currentItem()->type());
        listWidget->takeItem(listWidget->currentRow());
    }
}

void MainWindow::createCodeBlock(){
    int id = model->createCodeBlock();
    QListWidgetItem* item = new QListWidgetItem("",listWidget,id);
    item->setData(Qt::UserRole, "codeblock");
    item->setFlags(item->flags() | Qt::ItemIsEditable);
}

void MainWindow::listItemChanged(QListWidgetItem* item){
    QVector<int> ids;
    for(int i = 0; i < listWidget->count(); i++){
        ids.push_back(listWidget->item(i)->type());
    }
    model->setMainIdOrder(ids);
    if(item->type() < 1 || item->data(Qt::UserRole).toString() != "codeblock") return;
    model->setCode(item->type(), item->text());
}

void MainWindow::initDialogs(){
    createComponentDialog = new CreateComponentDialog(model);
    connect(createComponentDialog,SIGNAL(accepted()),this,SLOT(createComponent()));

    settingsDialog = new SettingsDialog();
    settingsDialog->setCompilerPath(model->getCompilerPath());
    settingsDialog->setArguments(model->getCompilerArguments().join(" "));
    connect(settingsDialog,SIGNAL(accepted()),this,SLOT(updateSettings()));
}

void MainWindow::initActions(){
    createComponentAction = new QAction(QIcon(":/icons/new_button.svg"),"Create Component");
    deleteComponentAction = new QAction(QIcon(":/icons/delete_button.svg"), "Delete Selected Component");
    deleteListItemAction = new QAction(QIcon(":/icons/delete_button.svg"), "Delete Selected List Item");
    createCodeBlockAction = new QAction(QIcon(":/icons/plus_button.svg"),"Create Code Block");
    generateAction = new QAction(QIcon(":/icons/generate_button.svg"),"Generate Source");
    runAction = new QAction(QIcon(":/icons/run_button.svg"),"Run");
    buildAction = new QAction(QIcon(":/icons/build_button.svg"),"Build");
    stopCompileAction = new QAction(QIcon(":/icons/stop_button.svg"),"Stop compile");
    settingsAction = new QAction(QIcon(":/icons/settings_button.svg"),"Settings");
    newProjectAction = new QAction(QIcon(":/icons/new_project_button.svg"),"New Project");
    loadProjectAction = new QAction(QIcon(":/icons/load_project_button.svg"),"Open Project");
    saveProjectAction = new QAction(QIcon(":/icons/save_project_button.svg"),"Save Project");

    stopCompileAction->setDisabled(true);
    saveProjectAction->setShortcut((QString)"Ctrl+S");

    connect(createComponentAction,SIGNAL(triggered()),this,SLOT(showCreateComponentDialog()));
    connect(deleteComponentAction,SIGNAL(triggered()),this,SLOT(deleteComponent()));
    connect(deleteListItemAction,SIGNAL(triggered()),this,SLOT(deleteListItem()));
    connect(createCodeBlockAction,SIGNAL(triggered()),this,SLOT(createCodeBlock()));
    connect(generateAction,SIGNAL(triggered()),this,SLOT(generateSource()));
    connect(runAction,SIGNAL(triggered()),this,SLOT(modelRun()));
    connect(buildAction,SIGNAL(triggered()),this,SLOT(modelCompile()));
    connect(stopCompileAction,SIGNAL(triggered()),this,SLOT(modelStopCompile()));
    connect(settingsAction,SIGNAL(triggered()),this,SLOT(showSettingsDialog()));
    connect(newProjectAction,SIGNAL(triggered()),this,SLOT(newProject()));
    connect(loadProjectAction,SIGNAL(triggered()),this,SLOT(loadProject()));
    connect(saveProjectAction,SIGNAL(triggered()),this,SLOT(saveProject()));
}

void MainWindow::initMenuBar(){
    menuBar = new QMenuBar();
    setMenuBar(menuBar);

    QMenu* fileMenu = new QMenu("File");
    menuBar->addMenu(fileMenu);
    fileMenu->addAction(newProjectAction);
    fileMenu->addAction(loadProjectAction);
    fileMenu->addAction(saveProjectAction);

    QMenu* createMenu = new QMenu("Create");
    menuBar->addMenu(createMenu);
    createMenu->addAction(createComponentAction);
    createMenu->addAction(createCodeBlockAction);
    createMenu->addAction(deleteComponentAction);

    QMenu* generateMenu = new QMenu("Generate");
    menuBar->addMenu(generateMenu);
    generateMenu->addAction(generateAction);

    QMenu* buildMenu = new QMenu("Build");
    menuBar->addMenu(buildMenu);
    buildMenu->addAction(runAction);
    buildMenu->addAction(buildAction);
    buildMenu->addAction(stopCompileAction);

    QMenu* settingsMenu = new QMenu("Settings");
    menuBar->addMenu(settingsMenu);
    settingsMenu->addAction(settingsAction);
}

void MainWindow::initComponentEditorSegment(){
    componentEditorWidget = new QWidget();
    componentEditorLayout = new QVBoxLayout();
    componentEditorLayout->setSpacing(0);
    componentEditorLayout->setContentsMargins(0,0,0,0);
    componentEditorToolBar = new QToolBar();
    componentEditorToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    QLabel* componentEditorLabel = new QLabel("Component Editor");
    componentEditorLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    componentEditorToolBar->addWidget(componentEditorLabel);

    toolBox = new QToolBox();
    componentEditorLayout->addWidget(componentEditorToolBar);
    componentEditorLayout->addWidget(toolBox);
    componentEditorWidget->setLayout(componentEditorLayout);
    centralSplitter->addWidget(componentEditorWidget);
    componentEditorWidget->resize(width()/3,0);

    componentEditorToolBar->addAction(createComponentAction);
    componentEditorToolBar->addAction(deleteComponentAction);
}

void MainWindow::initListSegment(){
    listSegmentWidget = new QWidget();
    listSegmentLayout = new QVBoxLayout();
    listSegmentLayout->setSpacing(0);
    listSegmentLayout->setContentsMargins(0,0,0,0);
    listSegmentToolBar = new QToolBar();
    QLabel* listSegmentLabel = new QLabel("Main List");
    listSegmentLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    listSegmentToolBar->addWidget(listSegmentLabel);

    listWidget = new QListWidget();
    listWidget->setDragEnabled(true);
    listWidget->setDropIndicatorShown(true);
    listWidget->setAcceptDrops(true);
    listWidget->setDefaultDropAction(Qt::MoveAction);
    listWidget->setStyleSheet("QListWidget::item {height:40px;border:2px solid gray;border-radius:5px;font-weight:bolder;} QListWidget::item::selected {color:black;}");
    listWidget->setWordWrap(true);

    listSegmentLayout->addWidget(listSegmentToolBar);
    listSegmentLayout->addWidget(listWidget);
    listSegmentWidget->setLayout(listSegmentLayout);
    centralSplitter->addWidget(listSegmentWidget);

    listSegmentToolBar->addAction(createCodeBlockAction);
    listSegmentToolBar->addAction(deleteListItemAction);

    connect(listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(changeSelectedComponent()));
    connect(listWidget,SIGNAL(itemChanged(QListWidgetItem*)),this,SLOT(listItemChanged(QListWidgetItem*)));
}

void MainWindow::initSourceSegment(){
    buildSplitter = new QSplitter(Qt::Vertical);

    sourceTextBrowser = new QTextBrowser();
    compileOutputBrowser = new QTextBrowser();

    buildToolBar = new QToolBar();
    buildToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);

    buildToolBar->addAction(generateAction);
    buildToolBar->addSeparator();
    buildToolBar->addAction(runAction);
    buildToolBar->addAction(buildAction);
    buildToolBar->addAction(stopCompileAction);

    buildSplitter->addWidget(sourceTextBrowser);
    buildSplitter->addWidget(buildToolBar);
    buildSplitter->addWidget(compileOutputBrowser);

    centralSplitter->addWidget(buildSplitter);
}

void MainWindow::generateSource(){
    bool allgood = true;

    foreach(ProcedureWidget* pw, procedureWidgets){
        allgood = pw->checkRequired() && allgood;
    }
    foreach(EnumeratorWidget* ew, enumeratorWidgets){
        allgood = ew->checkRequired() && allgood;
    }

    if(!allgood){
        sourceTextBrowser->setText("Missing required fields! Please check your components!");
        return;
    }

    QVector<int> ids;
    for(int i = 0; i < listWidget->count(); i++){
        ids.push_back(listWidget->item(i)->type());
    }
    model->setMainIdOrder(ids);
    sourceTextBrowser->setText(model->generateSource());
}

void MainWindow::showCreateComponentDialog(){
    createComponentDialog->clear();
    createComponentDialog->exec();
}

void MainWindow::showSettingsDialog(){
    settingsDialog->exec();
}

void MainWindow::updateSettings(){
    model->setCompilerPath(settingsDialog->getCompilerPath());
    model->setCompilerArguments(settingsDialog->getArguments());
}

void MainWindow::modelRun(){
    runAction->setDisabled(true);
    buildAction->setDisabled(true);
    stopCompileAction->setEnabled(true);
    model->run();
}

void MainWindow::modelCompile(){
    runAction->setDisabled(true);
    buildAction->setDisabled(true);
    stopCompileAction->setEnabled(true);
    model->compile();
}

void MainWindow::modelStopCompile(){
    model->stopCompile();
}

void MainWindow::showCompileOutput(QString output){
    compileOutputBrowser->setPlainText(output);
}

void MainWindow::allowCompile(){
    runAction->setEnabled(true);
    buildAction->setEnabled(true);
    stopCompileAction->setDisabled(true);
}

void MainWindow::showCompilerPathWarning(){
    compileOutputBrowser->setPlainText("Compiler path not set! Please go to the Settings menu and configure the compiler.");
}

void MainWindow::changeSelectedComponent(){
    if(listWidget->currentItem() == nullptr) return;

    ProcedureWidget* widget = nullptr;
    int id = listWidget->currentItem()->type();
    foreach(ProcedureWidget* pw, procedureWidgets){
        if(pw->getID() == id){
            widget = pw;
            break;
        }
    }
    if(widget != nullptr){
        toolBox->setCurrentIndex(toolBox->indexOf(widget));
    }
}

void MainWindow::newProject(){
    if(showDiscardWarning()){
        if(model->newProject()){
            setWindowTitle((QString)APP_NAME + " - " + model->getProjectName());
        }
    }
}

void MainWindow::saveProject(){
    if(model->saveProject()){
        setWindowTitle((QString)APP_NAME + " - " + model->getProjectName());
    }
}

void MainWindow::loadProject(){
    if(showDiscardWarning()){
        model->openProject();
    }
}

void MainWindow::showProjectSaveDialog(){
    QFileDialog fileDialog;
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    fileDialog.setFileMode(QFileDialog::AnyFile);
    fileDialog.setDefaultSuffix("lvpro");

    QString file = fileDialog.getSaveFileName();

    if(file == "") return;

    model->setProject(file);
}

void MainWindow::showProjectOpenDialog(){
    QFileDialog fileDialog;
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setFileMode(QFileDialog::AnyFile);
    fileDialog.setDefaultSuffix("lvpro");

    QString file = fileDialog.getOpenFileName();

    if(file == "") return;

    model->setProject(file);
}

void MainWindow::refresh(const SaveData& data){
    clear();
    setWindowTitle((QString)APP_NAME + " - " + data.projectName);

    QMap<int,QListWidgetItem*> listItems;

    foreach(const Component* component, data.components){
        ComponentType componentType = component->getType();
        if(componentType == COUNTING || componentType == LINSEARCH || componentType == MAXSEARCH || componentType == SELECTION || componentType == SUMMATION){
            ProcedureWidget* procedure = new ProcedureWidget(*component, model, this);
            connect(procedure,SIGNAL(useInMainChecked(QString,int)),this,SLOT(addListItem(QString,int)));
            connect(procedure,SIGNAL(useInMainUnchecked(int)),this,SLOT(deleteListItem(int)));
            toolBox->addItem(procedure,component->getName());
            procedureWidgets.push_back(procedure);
            if(component->getUseInMain()){
                QListWidgetItem* listItem = new QListWidgetItem(component->getName(), nullptr, component->getID());
                listItem->setData(Qt::UserRole,"component");
                listItems[component->getID()] = listItem;
            }
        }else{
            EnumeratorWidget* enumerator = new EnumeratorWidget(*component, model, this);
            toolBox->addItem(enumerator,component->getName());
            enumeratorWidgets.push_back(enumerator);
        }
    }

    foreach(const CodeBlock* codeBlock, data.codeblocks){
        QListWidgetItem* listItem = new QListWidgetItem(codeBlock->getCode(),nullptr,codeBlock->getID());
        listItem->setData(Qt::UserRole, "codeblock");
        listItem->setFlags(listItem->flags() | Qt::ItemIsEditable);
        listItems[codeBlock->getID()] = listItem;
    }

    for(int i = 0; i < data.mainIdOrder.size(); i++){
        listWidget->insertItem(i,listItems[data.mainIdOrder[i]]);
    }

    foreach(ProcedureWidget* procw, procedureWidgets){
        foreach(EnumeratorWidget* enorw, enumeratorWidgets){
            procw->addEnumeratorChoice(enorw->getName(), enorw->getID());
        }
    }

    foreach(const Struct* _struct, data.structs){
        StructWidget* structWidget = new StructWidget(*_struct, model, this);
        toolBox->addItem(structWidget,_struct->getName());
        structWidgets.push_back(structWidget);
    }
}

void MainWindow::clear(){
    while(toolBox->count()){
        toolBox->removeItem(toolBox->currentIndex());
    }
    listWidget->clear();
    sourceTextBrowser->clear();
    compileOutputBrowser->clear();

    procedureWidgets.clear();
    enumeratorWidgets.clear();
    structWidgets.clear();
}

bool MainWindow::showDiscardWarning(){
    QMessageBox msg(QMessageBox::Icon::Question, "Discard changes", "Unsaved changes might be lost!\nDo you want to continue?", QMessageBox::Yes | QMessageBox::No, this);
    msg.setDefaultButton(QMessageBox::No);
    int msg_res = msg.exec();

    if(msg_res != QMessageBox::Yes) return false;
    else return true;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(showDiscardWarning()){
        QMainWindow::closeEvent(event);
    }else{
        event->ignore();
    }
}


MainWindow::~MainWindow()
{
}

