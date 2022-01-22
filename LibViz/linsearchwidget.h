#ifndef LINSEARCHWIDGET_H
#define LINSEARCHWIDGET_H

#include <QCheckBox>
#include "procedurewidget.h"

class LinSearchWidget : public ProcedureWidget
{
    Q_OBJECT
public:
    explicit LinSearchWidget(QString name, QWidget *parent = nullptr);

    QMap<QString,QString> getData(){return QMap<QString,QString>();}

private:
    QGridLayout* gridlayout;

    //optimist
    QLabel* optimistLabel;
    QCheckBox* optimistCheckBox;

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

#endif // LINSEARCHWIDGET_H
