#ifndef STRUCTWIDGET_H
#define STRUCTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "memberwidget.h"
#include "custommethodwidget.h"
#include "model.h"

class StructWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StructWidget(int id, QString name, Model* model, QWidget *parent = nullptr);

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
