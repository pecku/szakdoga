#ifndef POPUPTEXTEDIT_H
#define POPUPTEXTEDIT_H

#include <QTextBrowser>

class MyTextEdit : public QTextBrowser
{
    Q_OBJECT
public:
    MyTextEdit(){}

protected:
    void focusInEvent(QFocusEvent *e) override {emit gotFocus();}

signals:
    void gotFocus();
};

#endif // POPUPTEXTEDIT_H
