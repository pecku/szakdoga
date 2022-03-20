#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>

class SettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SettingsDialog();
    QString getCompilerPath(){return compilerPathLineEdit->text();}
    QString getArguments(){return argumentsLineEdit->text();}
    void setCompilerPath(QString compilerPath){compilerPathLineEdit->setText(compilerPath);}
    void setArguments(QString compilerArguments){argumentsLineEdit->setText(compilerArguments);}

private:
    QPushButton* okButton;
    QPushButton* cancelButton;
    QLineEdit* compilerPathLineEdit;
    QLineEdit* argumentsLineEdit;
};

#endif // SETTINGSDIALOG_H
