#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define APP_NAME "LibViz"

#include <QMainWindow>
#include <QSplitter>
#include <QToolBox>
#include <QTextBrowser>
#include <QMenuBar>
#include <QListWidget>
#include <QToolBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QCloseEvent>

#include "procedurewidget.h"
#include "enumeratorwidget.h"
#include "structwidget.h"
#include "createcomponentdialog.h"
#include "settingsdialog.h"
#include "model.h"

/*!
 * \brief Class representing the main window of the application.
 * 
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

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
    QVector<StructWidget*> structWidgets;

    QAction* createComponentAction;
    QAction* deleteComponentAction;
    QAction* deleteListItemAction;
    QAction* createCodeBlockAction;
    QAction* generateAction;
    QAction* runAction;
    QAction* buildAction;
    QAction* stopCompileAction;
    QAction* settingsAction;
    QAction* newProjectAction;
    QAction* saveProjectAction;
    QAction* loadProjectAction;

    void initDialogs();
    void initActions();
    void initMenuBar();
    void initComponentEditorSegment();
    void initListSegment();
    void initSourceSegment();
    bool showDiscardWarning();

private slots:
    void showCreateComponentDialog();
    void createComponent();
    void deleteComponent();
    void addListItem(QString componentName, int componentID);
    void deleteListItem(int id);
    void deleteListItem();
    void createCodeBlock();
    void showSettingsDialog();
    void updateSettings();
    void generateSource();
    void modelRun();
    void modelCompile();
    void modelStopCompile();
    void showCompileOutput(QString output);
    void allowCompile();
    void showCompilerPathWarning();
    void listItemChanged(QListWidgetItem* item);
    void changeSelectedComponent();
    void newProject();
    void loadProject();
    void saveProject();
    void showProjectSaveDialog();
    void showProjectOpenDialog();
    void refresh(const SaveData& data);
    void clear();
};
#endif // MAINWINDOW_H
