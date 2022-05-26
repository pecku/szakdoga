#ifndef STRUCTWIDGET_H
#define STRUCTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "memberwidget.h"
#include "custommethodwidget.h"
#include "model.h"

/*!
 * \brief Class representing a struct's widget.
 * 
 */
class StructWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StructWidget(int id, QString name, Model* model, QWidget *parent = nullptr);
    StructWidget(const Struct& _struct, Model* model, QWidget *parent = nullptr);

    QString getName(){return name;}
    int getID(){return id;}

private:
    QString name;
    QVector<MemberWidget*> members;
    QVector<CustomMethodWidget*> customMethods;

    QLabel* nameLabel;
    QLabel* structLabel;
    QVBoxLayout* memberLayout;
    QVBoxLayout* customMethodLayout;

    void initSegments();
    void createMember(int id, QString type = "", QString name = "");
    void createCustomMethod(int id, QString header = "", QString body = "");
    void createMembers(QMap<int,Member> members);
    void createCustomMethods(QMap<int,CustomMethod> customMethods);

protected:
    const int id;
    Model* model;
    QGridLayout* gridlayout;
    QVBoxLayout* vboxlayout;

private slots:
    void onAddNewMemberClicked();
    void onAddNewMethodClicked();
    void memberChanged();
    void methodChanged();
    void deleteMember();
    void deleteMethod();

signals:

};

#endif // STRUCTWIDGET_H
