#ifndef CREATECOMPONENTDIALOG_H
#define CREATECOMPONENTDIALOG_H


#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include "modelkit.h"

enum CreateComponentDialogMode{PROCEDURE,ENUMERATOR};

class CreateComponentDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CreateComponentDialog();
    void setMode(CreateComponentDialogMode mode);
    QString getName(){return nameLineEdit->text();}
    CreateComponentDialogMode getMode(){return mode;}
    QVariant getComponent(){return componentTypeSelect->currentData();}
    void clear();

private:
    CreateComponentDialogMode mode;
    QPushButton* okButton;
    QPushButton* cancelButton;
    QLineEdit* nameLineEdit;
    QComboBox* componentTypeSelect;

signals:

};


#endif // CREATECOMPONENTDIALOG_H
