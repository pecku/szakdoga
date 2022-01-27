#ifndef PROCEDUREWIDGET_H
#define PROCEDUREWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QTextEdit>
#include <QCheckBox>
#include <QRadioButton>
#include "memberwidget.h"
#include "modelkit.h"

class ProcedureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProcedureWidget(QString name, ComponentType type, QWidget *parent = nullptr);

    void setName(QString name){nameLabel->setText(name);}
    QMap<MethodType,QString> getData();
    QMap<QString,QString> getMembers();
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
    QLabel* enorLabel;
    QComboBox* enorComboBox;
    QLabel* destructorLabel;
    QTextEdit* destructorTextEdit;
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
    QTextEdit* neutralTextEdit;

    //Value add( const Value& a, const Value& b) const
    QLabel* addLabel;
    QTextEdit* addTextEdit;

    //Value func(const Item& e) const
    QLabel* funcLabel;
    QTextEdit* funcTextEdit;

    //bool cond(const Item& e) const
    QLabel* condLabel;
    QTextEdit* condTextEdit;

    //void first()
    QLabel* firstLabel;
    QTextEdit* firstTextEdit;

    //bool whileCond(const Item& current) const
    QLabel* whileCondLabel;
    QTextEdit* whileCondTextEdit;

    QVBoxLayout* vboxlayout;

private slots:
    void onAddNewMemberClicked();

signals:

};

#endif // PROCEDUREWIDGET_H
