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

    centralSplitter->addWidget(new QTextEdit());
    sourceTextBrowser = new QTextBrowser();
    centralSplitter->addWidget(sourceTextBrowser);

    initMenuBar();
}

void MainWindow::createComponent(){
    QString name = createComponentDialog->getName();
    int component = createComponentDialog->getComponent().toInt();
    CreateComponentDialogMode mode = createComponentDialog->getMode();
    switch (mode) {
        case PROCEDURE:{
            ProcedureWidget* procedure = new ProcedureWidget(name, (ProcedureType)component);
            toolBox->addItem(procedure,name);
            procedureWidgets.push_back(procedure);
            break;
        }
        case ENUMERATOR:{
            EnumeratorWidget* enumerator = new EnumeratorWidget(name, (EnumeratorType)component);
            toolBox->addItem(enumerator,name);
            enumeratorWidgets.push_back(enumerator);
            break;
        }
    }

}

void MainWindow::initMenuBar(){
    menuBar = new QMenuBar();
    setMenuBar(menuBar);

    QMenu* createMenu = new QMenu("Create");
    menuBar->addMenu(createMenu);
    QAction* createProcedureAction = new QAction("Create Procedure");
    createMenu->addAction(createProcedureAction);
    connect(createProcedureAction,SIGNAL(triggered()),this,SLOT(showCreateProcedureDialog()));
    QAction* createEnumeratorAction = new QAction("Create Enumerator");
    createMenu->addAction(createEnumeratorAction);
    connect(createEnumeratorAction,SIGNAL(triggered()),this,SLOT(showCreateEnumeratorDialog()));

    QMenu* generateMenu = new QMenu("Generate");
    menuBar->addMenu(generateMenu);
    QAction* generateAction = new QAction("Generate Source");
    generateMenu->addAction(generateAction);
    connect(generateAction,SIGNAL(triggered()),this,SLOT(generateSource()));
}

void MainWindow::generateSource(){
    model->clear();
    for(ProcedureWidget* procedure : procedureWidgets){
        model->createProcedure(procedure->getName(), procedure->getType(), procedure->getData(), procedure->getMembers());
    }
    for(EnumeratorWidget* enumerator : enumeratorWidgets){
        model->createEnumerator(enumerator->getName(), enumerator->getType(), enumerator->getData(), enumerator->getMembers());
    }
    sourceTextBrowser->setText(model->generateSource());
}

void MainWindow::showCreateProcedureDialog(){
    createComponentDialog->setMode(PROCEDURE);
    showCreateComponentDialog();
}
void MainWindow::showCreateEnumeratorDialog(){
    createComponentDialog->setMode(ENUMERATOR);
    showCreateComponentDialog();
}

void MainWindow::showCreateComponentDialog(){
    createComponentDialog->clear();
    createComponentDialog->exec();
}

MainWindow::~MainWindow()
{
}

