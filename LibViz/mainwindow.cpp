#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    centralSplitter = new QSplitter(Qt::Horizontal);
    setCentralWidget(centralSplitter);
}

MainWindow::~MainWindow()
{
}

