#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(1000,700);

    model = new Model();
    connect(model, SIGNAL(haveCompileOutput()), this, SLOT(showCompileOutput()));
    connect(model, SIGNAL(compileProcessEnded()), this, SLOT(allowCompile()));
    connect(model, SIGNAL(compilerPathNotSet()), this, SLOT(showCompilerPathWarning()));

    createComponentDialog = new CreateComponentDialog();
    connect(createComponentDialog,SIGNAL(accepted()),this,SLOT(createComponent()));

    settingsDialog = new SettingsDialog();
    connect(settingsDialog,SIGNAL(accepted()),this,SLOT(updateSettings()));

    centralSplitter = new QSplitter(Qt::Horizontal);
    centralSplitter->setContentsMargins(4,4,4,4);
    setCentralWidget(centralSplitter);

    buildSplitter = new QSplitter(Qt::Vertical);
    buildSplitter->setContentsMargins(4,4,4,4);

    toolBox = new QToolBox();
    centralSplitter->addWidget(toolBox);
    toolBox->resize(width()/3,0);

    listView = new QListView();
    listView->setDragEnabled(true);
    listView->setDropIndicatorShown(true);
    listView->setAcceptDrops(true);
    listView->setDefaultDropAction(Qt::MoveAction);
    listView->setModel(new MyStringListModel());
    listView->setStyleSheet("QListView::item {height:40px;border:2px solid gray;border-radius:5px;font-weight:bolder;} QListView::item::selected {color:black;}");
    centralSplitter->addWidget(listView);

    initMenuBar();
    initBuildToolBar();
}

void MainWindow::createComponent(){
    QString name = createComponentDialog->getName();
    ComponentType componentType = (ComponentType)createComponentDialog->getComponent().toInt();
    if(componentType == COUNTING || componentType == LINSEARCH || componentType == MAXSEARCH || componentType == SELECTION || componentType == SUMMATION){
        ProcedureWidget* procedure = new ProcedureWidget(model->createComponent(name, componentType),name,componentType,model);
        toolBox->addItem(procedure,name);
        procedureWidgets.push_back(procedure);
        foreach(EnumeratorWidget* enorw, enumeratorWidgets){
            procedure->addEnumeratorChoice(enorw->getName());
        }
        listView->model()->insertRow(listView->model()->rowCount());
        listView->model()->setData(listView->model()->index(listView->model()->rowCount()-1,0), name);
    }else{
        EnumeratorWidget* enumerator = new EnumeratorWidget(model->createComponent(name, componentType),name,componentType,model);
        toolBox->addItem(enumerator,name);
        enumeratorWidgets.push_back(enumerator);
        foreach(ProcedureWidget* procw, procedureWidgets){
            procw->addEnumeratorChoice(name);
        }
    }
}

void MainWindow::createCodeBlock(){
    int id = model->createCodeBlock();
    QListWidgetItem* item = new QListWidgetItem("",listWidget,id);
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    connect(listWidget,SIGNAL(itemChanged(QListWidgetItem*)),this,SLOT(listItemChanged(QListWidgetItem*)));
}
void MainWindow::initMenuBar(){
    menuBar = new QMenuBar();
    setMenuBar(menuBar);

    QMenu* createMenu = new QMenu("Create");
    menuBar->addMenu(createMenu);
    QAction* createComponentAction = new QAction("Create Component");
    createMenu->addAction(createComponentAction);
    connect(createComponentAction,SIGNAL(triggered()),this,SLOT(showCreateComponentDialog()));

    QMenu* generateMenu = new QMenu("Generate");
    menuBar->addMenu(generateMenu);
    QAction* generateAction = new QAction("Generate Source");
    generateMenu->addAction(generateAction);
    connect(generateAction,SIGNAL(triggered()),this,SLOT(generateSource()));

    QMenu* buildMenu = new QMenu("Build");
    menuBar->addMenu(buildMenu);
    runAction = new QAction(QIcon(":/icons/run_button.svg"),"Run");
    buildMenu->addAction(runAction);
    buildAction = new QAction(QIcon(":/icons/build_button.svg"),"Build");
    buildMenu->addAction(buildAction);
    stopCompileAction = new QAction(QIcon(":/icons/stop_button.svg"),"Stop compile");
    buildMenu->addAction(stopCompileAction);
    stopCompileAction->setDisabled(true);
    connect(runAction,SIGNAL(triggered()),this,SLOT(modelRun()));
    connect(buildAction,SIGNAL(triggered()),this,SLOT(modelCompile()));
    connect(stopCompileAction,SIGNAL(triggered()),this,SLOT(modelStopCompile()));

    QMenu* settingsMenu = new QMenu("Settings");
    menuBar->addMenu(settingsMenu);
    QAction* settingsAction = new QAction("Settings");
    settingsMenu->addAction(settingsAction);
    connect(settingsAction,SIGNAL(triggered()),this,SLOT(showSettingsDialog()));
}

void MainWindow::initBuildToolBar(){
    sourceTextBrowser = new QTextBrowser();
    compileOutputBrowser = new QTextBrowser();

    buildToolBar = new QToolBar();
    buildToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);

    buildToolBar->addAction(runAction);
    buildToolBar->addAction(buildAction);
    buildToolBar->addAction(stopCompileAction);

    buildSplitter->addWidget(sourceTextBrowser);
    buildSplitter->addWidget(buildToolBar);
    buildSplitter->addWidget(compileOutputBrowser);

    centralSplitter->addWidget(buildSplitter);
}

void MainWindow::generateSource(){
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

void MainWindow::showCompileOutput(){
    compileOutputBrowser->setPlainText(model->getCompileOutput());
}

void MainWindow::allowCompile(){
    runAction->setEnabled(true);
    buildAction->setEnabled(true);
    stopCompileAction->setDisabled(true);
}

void MainWindow::showCompilerPathWarning(){
    compileOutputBrowser->setPlainText("Compiler path not set! Please go to the Settings menu and configure the compiler.");
}

MainWindow::~MainWindow()
{
}

