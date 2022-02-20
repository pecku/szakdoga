#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(1000,700);

    model = new Model();
    connect(model, SIGNAL(haveCompileOutput()), this, SLOT(showCompileOutput()));

    createComponentDialog = new CreateComponentDialog();
    connect(createComponentDialog,SIGNAL(accepted()),this,SLOT(createComponent()));

    settingsDialog = new SettingsDialog();
    connect(settingsDialog,SIGNAL(accepted()),this,SLOT(updateSettings()));

    centralSplitter = new QSplitter(Qt::Horizontal);
    centralSplitter->setContentsMargins(4,4,4,4);
    setCentralWidget(centralSplitter);

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

    sourceTextBrowser = new QTextBrowser();
    centralSplitter->addWidget(sourceTextBrowser);

    compileOutputBrowser = new QTextBrowser();
    centralSplitter->addWidget(compileOutputBrowser);

    initMenuBar();
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
    QAction* compileAction = new QAction("Compile Source");
    buildMenu->addAction(compileAction);
    connect(compileAction,SIGNAL(triggered()),this,SLOT(modelCompile()));

    QMenu* settingsMenu = new QMenu("Settings");
    menuBar->addMenu(settingsMenu);
    QAction* settingsAction = new QAction("Settings");
    settingsMenu->addAction(settingsAction);
    connect(settingsAction,SIGNAL(triggered()),this,SLOT(showSettingsDialog()));
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

void MainWindow::modelCompile(){
    model->compile();
}

void MainWindow::showCompileOutput(){
    compileOutputBrowser->setPlainText(model->getCompileOutput());
}

MainWindow::~MainWindow()
{
}

