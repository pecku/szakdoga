#ifndef COUNTINGWIDGET_H
#define COUNTINGWIDGET_H

#include "procedurewidget.h"

class CountingWidget : public ProcedureWidget
{
    Q_OBJECT
public:
    explicit CountingWidget(QString name, QWidget *parent = nullptr);

    QMap<QString,QString> getData(){return QMap<QString,QString>();}

private:
    QGridLayout* gridlayout;

    //bool cond(const Item& e) const
    QLabel* condLabel;
    QTextEdit* condTextEdit;

    //void first()
    QLabel* firstLabel;
    QTextEdit* firstTextEdit;

    //bool whileCond(const Item& current) const
    QLabel* whileCondLabel;
    QTextEdit* whileCondTextEdit;

signals:

};

#endif // COUNTINGWIDGET_H
