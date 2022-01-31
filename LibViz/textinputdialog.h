#ifndef TEXTINPUTDIALOG_H
#define TEXTINPUTDIALOG_H

#include <QDialog>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class TextInputDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TextInputDialog();
    QString getText(){return textEdit->toPlainText();}

private:
    QTextEdit* textEdit;
    QPushButton* saveButton;
    QPushButton* cancelButton;
};

#endif // TEXTINPUTDIALOG_H
