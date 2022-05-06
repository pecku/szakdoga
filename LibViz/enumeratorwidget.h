#ifndef ENUMERATORWIDGET_H
#define ENUMERATORWIDGET_H

#include <QWidget>
#include "componentwidget.h"

class EnumeratorWidget : public ComponentWidget
{
    Q_OBJECT
public:
    explicit EnumeratorWidget(int id, QString name, ComponentType type, Model* model, QWidget *parent = nullptr);
    EnumeratorWidget(const Component& component, Model* model, QWidget *parent = nullptr);

    bool checkRequired();

private:
    void initSegments();
    void connectSignals();

    //void first()
    QLabel* firstLabel;
    PopUpTextEdit* firstTextEdit;

    //void next()
    QLabel* nextLabel;
    PopUpTextEdit* nextTextEdit;

    //bool end() const
    QLabel* endLabel;
    PopUpTextEdit* endTextEdit;

    //Item current() const
    QLabel* currentLabel;
    PopUpTextEdit* currentTextEdit;

signals:

};

#endif // ENUMERATORWIDGET_H
