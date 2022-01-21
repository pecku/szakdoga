#ifndef MEMBERWIDGET_H
#define MEMBERWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QHBoxLayout>

class MemberWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MemberWidget(QWidget *parent = nullptr);

    QString getType(){return type->text();}
    QString getName(){return name->text();}

private:
    QLineEdit* type;
    QLineEdit* name;
    QHBoxLayout* hboxlayout;

signals:

};

#endif // MEMBERWIDGET_H
