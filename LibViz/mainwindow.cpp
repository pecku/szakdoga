#include "mainwindow.h"
#include "selectionwidget.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    centralSplitter = new QSplitter(Qt::Horizontal);
    setCentralWidget(centralSplitter);

    centralSplitter->addWidget(new SelectionWidget("Hello"));
}

MainWindow::~MainWindow()
{
}

