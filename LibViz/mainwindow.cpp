#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    centralSplitter = new QSplitter(Qt::Horizontal);
    centralSplitter->setContentsMargins(4,4,4,4);
    setCentralWidget(centralSplitter);

    toolBox = new QToolBox();
    centralSplitter->addWidget(toolBox);

    centralSplitter->addWidget(new QTextEdit());
    centralSplitter->addWidget(new QTextBrowser());

    toolBox->addItem(new ProcedureWidget("MyCounting", COUNTING),"MyCounting");
    toolBox->addItem(new ProcedureWidget("MyLinSearch", LINSEARCH),"MyLinSearch");
    toolBox->addItem(new ProcedureWidget("MyMaxSearch", MAXSEARCH),"MyMaxSearch");
    toolBox->addItem(new ProcedureWidget("MySelection", SELECTION),"MySelection");
    toolBox->addItem(new ProcedureWidget("MySummation", SUMMATION),"MySummation");
    toolBox->addItem(new EnumeratorWidget("MyEnumerator", SEQINFILE),"MyEnumerator");
}

MainWindow::~MainWindow()
{
}

