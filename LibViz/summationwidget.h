#ifndef SUMMATIONWIDGET_H
#define SUMMATIONWIDGET_H

#include "procedurewidget.h"

class SummationWidget : public ProcedureWidget
{
    Q_OBJECT
public:
    explicit SummationWidget(QString name, QWidget *parent = nullptr);

    QMap<QString,QString> getData(){return QMap<QString,QString>();}

private:
    QGridLayout* gridlayout;

    //Value type
    QLabel* valueLabel;
    QLineEdit* valueLineEdit;

    //Value neutral() const
    QLabel* neutralLabel;
    QTextEdit* neutralTextEdit;

    //Value add( const Value& a, const Value& b) const
    QLabel* addLabel;
    QTextEdit* addTextEdit;

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

#endif // SUMMATIONWIDGET_H
