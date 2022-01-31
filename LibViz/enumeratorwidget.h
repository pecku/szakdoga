#ifndef ENUMERATORWIDGET_H
#define ENUMERATORWIDGET_H

#include <QWidget>
#include <QMap>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include "memberwidget.h"
#include "model.h"

class EnumeratorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EnumeratorWidget(int id, QString name, ComponentType type, Model* model, QWidget *parent = nullptr);

    QMap<QString,QString> getMembers();
    QMap<MethodType,QString> getData();
    QString getName(){return name;}
    ComponentType getType(){return type;}

private:
    const int id;
    QString name;
    ComponentType type;
    Model* model;

    QLabel* nameLabel;
    QLabel* parentClassLabel;
    QVector<MemberWidget*> members;
    QVBoxLayout* memberLayout;
    QLabel* itemTypeLabel;
    QLineEdit* itemTypeLineEdit;
    QLabel* destructorLabel;
    QTextEdit* destructorTextEdit;

    //void first()
    QLabel* firstLabel;
    QTextEdit* firstTextEdit;

    //void next()
    QLabel* nextLabel;
    QTextEdit* nextTextEdit;

    //bool end() const
    QLabel* endLabel;
    QTextEdit* endTextEdit;

    //Item current() const
    QLabel* currentLabel;
    QTextEdit* currentTextEdit;

    QGridLayout* gridlayout;
    QVBoxLayout* vboxlayout;

private slots:
    void onAddNewMemberClicked();

signals:

};

#endif // ENUMERATORWIDGET_H
