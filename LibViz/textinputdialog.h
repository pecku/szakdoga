#ifndef TEXTINPUTDIALOG_H
#define TEXTINPUTDIALOG_H

#include <QDialog>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

/*!
 * \brief Class representing a dialog for a text input.
 * 
 */
class TextInputDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TextInputDialog();
    QString getText(){return textEdit->toPlainText();}
    void exec(QString text){textEdit->setText(text); exec();}

private:
    QTextEdit* textEdit;
    QPushButton* saveButton;
    QPushButton* cancelButton;
    using QDialog::exec;
};

#endif // TEXTINPUTDIALOG_H
