#ifndef POPUPTEXTEDIT_H
#define POPUPTEXTEDIT_H

#include <QTextBrowser>
#include <textinputdialog.h>
#include "modelkit.h"

class PopUpTextEdit : public QTextBrowser
{
    Q_OBJECT
public:
    PopUpTextEdit(MethodType methodType);

    MethodType getMethodType(){return methodType;}

protected:
    void focusInEvent(QFocusEvent *e) override;

private:
    MethodType methodType;
    TextInputDialog* inputDialog;

private slots:
    void getTextFromInputDialog();

signals:
    void textChanged();
};

#endif // POPUPTEXTEDIT_H
