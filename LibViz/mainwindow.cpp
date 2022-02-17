#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(1000,700);

    createComponentDialog = new CreateComponentDialog();
    connect(createComponentDialog,SIGNAL(accepted()),this,SLOT(createComponent()));

    model = new Model();

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
}

void MainWindow::generateSource(){
    sourceTextBrowser->setText(model->generateSource());
}

void MainWindow::showCreateComponentDialog(){
    createComponentDialog->clear();
    createComponentDialog->exec();
}

MainWindow::~MainWindow()
{
}

