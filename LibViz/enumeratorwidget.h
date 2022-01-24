#ifndef ENUMERATORWIDGET_H
#define ENUMERATORWIDGET_H

#include <QWidget>
#include <QMap>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include "memberwidget.h"

enum EnumeratorType{DEFAULT, ARRAY, INTERVAL, STRINGSTREAM, SEQINFILE};

class EnumeratorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EnumeratorWidget(QString name, EnumeratorType type, QWidget *parent = nullptr);

    virtual QMap<QString,QString> getData(){return QMap<QString,QString>();}

private:
    EnumeratorType type;

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

protected:
    QVBoxLayout* vboxlayout;

    void setParentClass(QString parentClass){parentClassLabel->setText(parentClass);}
    QMap<QString,QString> getMembers();


private slots:
    void onAddNewMemberClicked();

signals:

};

#endif // ENUMERATORWIDGET_H
