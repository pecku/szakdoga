#ifndef SELECTIONWIDGET_H
#define SELECTIONWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QGridLayout>
#include <QLineEdit>
#include <QTextEdit>
#include "procedurewidget.h"

class SelectionWidget : public ProcedureWidget
{
    Q_OBJECT
public:
    explicit SelectionWidget(QString name, QWidget *parent = nullptr);

    QMap<QString,QString> getData(){return QMap<QString,QString>();}

private:
    QGridLayout* gridlayout;

    //template < typename Item >
    QLabel* itemTypeLabel;
    QLineEdit* itemTypeLineEdit;

    //bool cond(const Item& e) const
    QLabel* condLabel;
    QTextEdit* condTextEdit;

    //void first()
    QLabel* firstLabel;
    QTextEdit* firstTextEdit;

    //bool whileCond(const Item& current) const
    QLabel* whileCondLabel;
    QTextEdit* whileCondTextEdit;

    //destructor
    QLabel* destructorLabel;
    QTextEdit* destructorTextEdit;

    //addEnumerator(Enumerator<Item>* en)
    QLabel* enorLabel;
    QComboBox* enorComboBox;

signals:

};

#endif // SELECTIONWIDGET_H
