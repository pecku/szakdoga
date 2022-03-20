#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QToolBox>
#include <QTextBrowser>
#include <QMenuBar>
#include <QListWidget>
#include <QToolBar>
#include <QMessageBox>

#include "procedurewidget.h"
#include "enumeratorwidget.h"
#include "createcomponentdialog.h"
#include "settingsdialog.h"
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
    SettingsDialog* settingsDialog;

    QMenuBar* menuBar;

    QSplitter* centralSplitter;
    QWidget* componentEditorWidget;
    QVBoxLayout* componentEditorLayout;
    QWidget* listSegmentWidget;
    QVBoxLayout* listSegmentLayout;
    QSplitter* buildSplitter;

    QToolBar* componentEditorToolBar;
    QToolBar* listSegmentToolBar;
    QToolBar* buildToolBar;
    QToolBox* toolBox;
    QListWidget* listWidget;
    QTextBrowser* sourceTextBrowser;
    QTextBrowser* compileOutputBrowser;

    QVector<ProcedureWidget*> procedureWidgets;
    QVector<EnumeratorWidget*> enumeratorWidgets;

    QAction* createComponentAction;
    QAction* deleteComponentAction;
    QAction* createCodeBlockAction;
    QAction* generateAction;
    QAction* runAction;
    QAction* buildAction;
    QAction* stopCompileAction;
    QAction* settingsAction;

    void initDialogs();
    void initActions();
    void initMenuBar();
    void initComponentEditorSegment();
    void initListSegment();
    void initSourceSegment();

private slots:
    void showCreateComponentDialog();
    void createComponent();
    void deleteComponent();
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
    void listItemChanged(QListWidgetItem* item);
};
#endif // MAINWINDOW_H
