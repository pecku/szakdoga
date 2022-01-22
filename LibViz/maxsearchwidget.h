#ifndef MAXSEARCHWIDGET_H
#define MAXSEARCHWIDGET_H

#include <QRadioButton>
#include "procedurewidget.h"

class MaxSearchWidget : public ProcedureWidget
{
    Q_OBJECT
public:
    explicit MaxSearchWidget(QString name, QWidget *parent = nullptr);

    QMap<QString,QString> getData(){return QMap<QString,QString>();}

private:
    QGridLayout* gridlayout;

    //Value type
    QLabel* valueLabel;
    QLineEdit* valueLineEdit;

    //compare
    QLabel* compareLabel;
    QRadioButton* greaterRadioButton;
    QRadioButton* lessRadioButton;

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

signals:

};

#endif // MAXSEARCHWIDGET_H
