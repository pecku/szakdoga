#ifndef POPUPTEXTEDIT_H
#define POPUPTEXTEDIT_H

#include <QTextBrowser>
#include "textinputdialog.h"
#include "modelkit.h"

/*!
 * \brief Class representing the text edit that has a pop-up input dialog.
 * 
 */
class PopUpTextEdit : public QTextBrowser
{
    Q_OBJECT
public:
    PopUpTextEdit();
    PopUpTextEdit(MethodType methodType);

    MethodType getMethodType(){return methodType;}

protected:
    void focusInEvent(QFocusEvent *e) override;

private:
    bool customMethod;
    MethodType methodType;
    TextInputDialog* inputDialog;

private slots:
    void getTextFromInputDialog();

signals:
    void textChanged();
};

#endif // POPUPTEXTEDIT_H
