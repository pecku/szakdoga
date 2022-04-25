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
    explicit MemberWidget(const int id, QString type = "", QString name = "", QWidget *parent = nullptr);

    QString getType(){return typeLineEdit->text();}
    QString getName(){return nameLineEdit->text();}
    int getID(){return id;}

private:
    const int id;
    QLineEdit* typeLineEdit;
    QLineEdit* nameLineEdit;
    QPushButton* deleteButton;
    QHBoxLayout* hboxlayout;

signals:
    void edited();
    void deleteMe();
};

#endif // MEMBERWIDGET_H
