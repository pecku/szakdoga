#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QToolBox>
#include <QTextBrowser>

#include "procedurewidget.h"
#include "enumeratorwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QSplitter* centralSplitter;
    QToolBox* toolBox;
};
#endif // MAINWINDOW_H
