#ifndef COMPONENTWIDGET_H
#define COMPONENTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QWhatsThis>
#include "memberwidget.h"
#include "custommethodwidget.h"
#include "model.h"
#include "popuptextedit.h"

class ComponentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ComponentWidget(int id, QString name, ComponentType type, Model* model, QWidget *parent = nullptr);

    QString getName(){return name;}
    ComponentType getType(){return type;}
    int getID(){return id;}

    virtual bool checkRequired() = 0;

private:
    QString name;
    bool objectNameApproved;
    QVector<MemberWidget*> members;
    QVector<CustomMethodWidget*> customMethods;

    QLabel* nameLabel;
    QLabel* parentClassLabel;
    QVBoxLayout* memberLayout;
    QVBoxLayout* customMethodLayout;

    void initSegments();

protected:
    ComponentType type;
    const int id;
    Model* model;
    QGridLayout* gridlayout;
    QVBoxLayout* vboxlayout;

    QLabel* objectNameLabel;
    QLineEdit* objectNameLineEdit;
    QLabel* itemTypeLabel;
    QLineEdit* itemTypeLineEdit;
    QLabel* destructorLabel;
    PopUpTextEdit* destructorTextEdit;

    bool checkRequiredBase();
    void connectSignals();
    void createMember(int id, QString type = "", QString name = "");
    void createCustomMethod(int id, QString header = "", QString body = "");
    void createMembers(QMap<int,Member> members);
    void createCustomMethods(QMap<int,CustomMethod> customMethods);

private slots:
    void onAddNewMemberClicked();
    void onAddNewMethodClicked();
    void memberChanged();
    void methodChanged();
    void objectNameChanged();
    void itemTypeChanged();
    void deleteMember();
    void deleteMethod();
    void popUpTextChanged();
    void constructorParameterChanged();

signals:

};

#endif // COMPONENTWIDGET_H
