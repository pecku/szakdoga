#ifndef PROCEDUREWIDGET_H
#define PROCEDUREWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QTextEdit>
#include "memberwidget.h"

class ProcedureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProcedureWidget(QWidget *parent = nullptr);

    void setName(QString name){nameLabel->setText(name);}
    virtual QMap<QString,QString> getData() = 0;

private:
    QLabel* nameLabel;
    QLabel* parentClassLabel;    
    QVector<MemberWidget*> members;
    QVBoxLayout* memberLayout;
    QLabel* itemTypeLabel;
    QLineEdit* itemTypeLineEdit;
    QLabel* enorLabel;
    QComboBox* enorComboBox;
    QLabel* destructorLabel;
    QTextEdit* destructorTextEdit;
    QGridLayout* gridlayout;

protected:
    QVBoxLayout* vboxlayout;

    void setParentClass(QString parentClass){parentClassLabel->setText(parentClass);}
    QMap<QString,QString> getMembers();


private slots:
    void onAddNewMemberClicked();

signals:

};

#endif // PROCEDUREWIDGET_H
