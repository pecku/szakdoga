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
    QString getName(){return nameLineEdit->text();}
    QVariant getComponent(){return componentTypeSelect->currentData();}
    void clear();

private:
    QPushButton* okButton;
    QPushButton* cancelButton;
    QLineEdit* nameLineEdit;
    QComboBox* componentTypeSelect;

private slots:
    void wantToAccept();

signals:

};


#endif // CREATECOMPONENTDIALOG_H
