#ifndef CUSTOMMETHODWIDGET_H
#define CUSTOMMETHODWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include "popuptextedit.h"

/*!
 * \brief Class representing the widget for a custom method.
 * 
 */
class CustomMethodWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomMethodWidget(int id, QString header = "", QString body = "", QWidget *parent = nullptr);

    QString getHeader(){return headerLineEdit->text();}
    QString getBody(){return bodyPopUpTextEdit->toPlainText();}
    int getID(){return id;}

private:
    const int id;
    QLineEdit* headerLineEdit;
    PopUpTextEdit* bodyPopUpTextEdit;
    QPushButton* deleteButton;
    QHBoxLayout* hboxlayout;
    QVBoxLayout* vboxlayout;

signals:
    void edited();
    void deleteMe();
};

#endif // CUSTOMMETHODWIDGET_H

