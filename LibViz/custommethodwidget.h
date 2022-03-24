#ifndef CUSTOMMETHODWIDGET_H
#define CUSTOMMETHODWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include "popuptextedit.h"

class CustomMethodWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomMethodWidget(int id, QWidget *parent = nullptr);

    QString getHeader(){return header->text();}
    QString getBody(){return body->toPlainText();}
    int getID(){return id;}

private:
    const int id;
    QLineEdit* header;
    PopUpTextEdit* body;
    QPushButton* deleteButton;
    QVBoxLayout* hboxlayout;

signals:
    void edited();
    void deleteMe();
};

#endif // CUSTOMMETHODWIDGET_H

