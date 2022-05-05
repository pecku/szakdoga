#ifndef PROCEDUREWIDGET_H
#define PROCEDUREWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QRadioButton>
#include "componentwidget.h"

class ProcedureWidget : public ComponentWidget
{
    Q_OBJECT
public:
    explicit ProcedureWidget(int id, QString name, ComponentType type, Model* model, QWidget *parent = nullptr);
    ProcedureWidget(const Component& component, Model* model, QWidget *parent = nullptr);

    void addEnumeratorChoice(QString enumeratorName, int enumeratorID);
    void removeEnumeratorChoice(int enumeratorID);
    void selectEnumerator(QString enumeratorName);
    bool checkRequired();

private:
    void initSegments();
    void connectSignals();

    QLabel* useInMainLabel;
    QCheckBox* useInMainCheckBox;

    //enumerator
    QLabel* enorLabel;
    QComboBox* enorComboBox;

    //optimist
    QLabel* optimistLabel;
    QCheckBox* optimistCheckBox;

    //Value type
    QLabel* valueLabel;
    QLineEdit* valueLineEdit;

    //compare
    QLabel* compareLabel;
    QRadioButton* greaterRadioButton;
    QRadioButton* lessRadioButton;

    //Value neutral() const
    QLabel* neutralLabel;
    PopUpTextEdit* neutralTextEdit;

    //Value add( const Value& a, const Value& b) const
    QLabel* addLabel;
    PopUpTextEdit* addTextEdit;

    //Value func(const Item& e) const
    QLabel* funcLabel;
    PopUpTextEdit* funcTextEdit;

    //bool cond(const Item& e) const
    QLabel* condLabel;
    PopUpTextEdit* condTextEdit;

    //void first()
    QLabel* firstLabel;
    PopUpTextEdit* firstTextEdit;

    //bool whileCond(const Item& current) const
    QLabel* whileCondLabel;
    PopUpTextEdit* whileCondTextEdit;

private slots:
    void useInMainChanged();
    void enorChanged(int index);
    void optimistChanged();
    void valueChanged();
    void compareChanged();

signals:
    void useInMainChecked(QString componentName, int componentID);
    void useInMainUnchecked(int componentID);
};

#endif // PROCEDUREWIDGET_H
