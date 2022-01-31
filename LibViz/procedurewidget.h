#ifndef PROCEDUREWIDGET_H
#define PROCEDUREWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QRadioButton>
#include "memberwidget.h"
#include "model.h"
#include "popuptextedit.h"

class ProcedureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProcedureWidget(int id, QString name, ComponentType type, Model* model, QWidget *parent = nullptr);

    void setName(QString name){nameLabel->setText(name);}
    QMap<MethodType,QString> getData();
    QMap<QString,QString> getMembers();
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
    QLabel* enorLabel;
    QComboBox* enorComboBox;
    QLabel* destructorLabel;
    PopUpTextEdit* destructorTextEdit;
    QGridLayout* gridlayout;

    //optimist
    QLabel* optimistLabel;
    QCheckBox* optimistCheckBox;

    //Value type
    QLabel* valueLabel;
    QLineEdit* valueLineEdit;

    //compare
    QLabel* compareLabel;
    QRadioButton* greaterRadioButton;
    QRadioButton* lessRadioButton;

    //Value neutral() const
    QLabel* neutralLabel;
    PopUpTextEdit* neutralTextEdit;

    //Value add( const Value& a, const Value& b) const
    QLabel* addLabel;
    PopUpTextEdit* addTextEdit;

    //Value func(const Item& e) const
    QLabel* funcLabel;
    PopUpTextEdit* funcTextEdit;

    //bool cond(const Item& e) const
    QLabel* condLabel;
    PopUpTextEdit* condTextEdit;

    //void first()
    QLabel* firstLabel;
    PopUpTextEdit* firstTextEdit;

    //bool whileCond(const Item& current) const
    QLabel* whileCondLabel;
    PopUpTextEdit* whileCondTextEdit;

    QVBoxLayout* vboxlayout;

private slots:
    void onAddNewMemberClicked();
    void memberChanged();
    void itemTypeChanged();
    void optimistChanged();
    void valueChanged();
    void compareChanged();
    void popUpTextChanged();

signals:

};

#endif // PROCEDUREWIDGET_H
