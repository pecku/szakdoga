#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QToolBox>
#include <QTextBrowser>
#include <QMenuBar>
#include <QListView>
#include <QStringListModel>

#include "procedurewidget.h"
#include "enumeratorwidget.h"
#include "createcomponentdialog.h"
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
    QMenuBar* menuBar;
    QSplitter* centralSplitter;
    QToolBox* toolBox;
    QListView* listView;
    QTextBrowser* sourceTextBrowser;
    QVector<ProcedureWidget*> procedureWidgets;
    QVector<EnumeratorWidget*> enumeratorWidgets;

    void initMenuBar();

    void asd();

private slots:
    void showCreateComponentDialog();
    void createComponent();
    void generateSource();
};
#endif // MAINWINDOW_H
