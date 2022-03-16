#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QToolBox>
#include <QTextBrowser>
#include <QMenuBar>
#include <QListView>
#include <QStringListModel>
#include <QToolBar>

#include "procedurewidget.h"
#include "enumeratorwidget.h"
#include "createcomponentdialog.h"
#include "settingsdialog.h"
#include "model.h"

class MyStringListModel : public QStringListModel{
    Q_OBJECT

public:
    MyStringListModel(QWidget *parent = nullptr) : QStringListModel(parent){}

    Qt::ItemFlags flags(const QModelIndex& ind) const override {
        if(ind.row() < 0){
            return Qt::ItemFlags({Qt::ItemIsDragEnabled,Qt::ItemIsEditable,Qt::ItemIsEnabled,
                                  Qt::ItemIsSelectable,Qt::ItemNeverHasChildren,Qt::ItemIsDropEnabled});
        }
        return Qt::ItemFlags({Qt::ItemIsDragEnabled,Qt::ItemIsEditable,Qt::ItemIsEnabled,
                              Qt::ItemIsSelectable,Qt::ItemNeverHasChildren});
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Model* model;
    CreateComponentDialog* createComponentDialog;
    SettingsDialog* settingsDialog;
    QMenuBar* menuBar;
    QSplitter* centralSplitter;
    QSplitter* buildSplitter;
    QToolBar* buildToolBar;
    QToolBox* toolBox;
    QListView* listView;
    QTextBrowser* sourceTextBrowser;
    QTextBrowser* compileOutputBrowser;
    QVector<ProcedureWidget*> procedureWidgets;
    QVector<EnumeratorWidget*> enumeratorWidgets;

    QAction* runAction;
    QAction* buildAction;
    QAction* stopCompileAction;

    void initMenuBar();
    void initBuildToolBar();

    void asd();

private slots:
    void showCreateComponentDialog();
    void createComponent();
    void createCodeBlock();
    void showSettingsDialog();
    void updateSettings();
    void generateSource();
    void modelRun();
    void modelCompile();
    void modelStopCompile();
    void showCompileOutput();
    void allowCompile();
    void showCompilerPathWarning();
};
#endif // MAINWINDOW_H
