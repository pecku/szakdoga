#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QToolBox>
#include <QTextBrowser>
#include <QMenuBar>

#include "procedurewidget.h"
#include "enumeratorwidget.h"
#include "createcomponentdialog.h"
#include "model.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Model* model;
    CreateComponentDialog* createComponentDialog;
    QMenuBar* menuBar;
    QSplitter* centralSplitter;
    QToolBox* toolBox;
    QTextBrowser* sourceTextBrowser;
    QVector<ProcedureWidget*> procedureWidgets;
    QVector<EnumeratorWidget*> enumeratorWidgets;

    void initMenuBar();

private slots:
    void showCreateComponentDialog();
    void createComponent();
    void generateSource();
};
#endif // MAINWINDOW_H
