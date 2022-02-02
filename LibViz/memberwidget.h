#ifndef MEMBERWIDGET_H
#define MEMBERWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

class MemberWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MemberWidget(int id, QWidget *parent = nullptr);

    QString getType(){return type->text();}
    QString getName(){return name->text();}
    int getID(){return id;}

private:
    const int id;
    QLineEdit* type;
    QLineEdit* name;
    QPushButton* deleteButton;
    QHBoxLayout* hboxlayout;

signals:
    void edited();
    void deleteMe();
};

#endif // MEMBERWIDGET_H
