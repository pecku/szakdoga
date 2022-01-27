#ifndef ENUMERATORWIDGET_H
#define ENUMERATORWIDGET_H

#include <QWidget>
#include <QMap>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include "memberwidget.h"
#include "modelkit.h"

class EnumeratorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EnumeratorWidget(QString name, ComponentType type, QWidget *parent = nullptr);

    QMap<QString,QString> getMembers();
    QMap<MethodType,QString> getData();
    QString getName(){return name;}
    ComponentType getType(){return type;}

private:
    QString name;
    ComponentType type;

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
