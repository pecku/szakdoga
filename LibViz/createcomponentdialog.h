#ifndef CREATECOMPONENTDIALOG_H
#define CREATECOMPONENTDIALOG_H


#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include "model.h"

/*!
 * \brief Class representing the dialog for creating a new component.
 * 
 */
class CreateComponentDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CreateComponentDialog(Model* model);
    QString getName(){return nameLineEdit->text();}
    QVariant getComponent(){return componentTypeSelect->currentData();}
    void clear();

private:
    Model* model;
    QPushButton* okButton;
    QPushButton* cancelButton;
    QLineEdit* nameLineEdit;
    QComboBox* componentTypeSelect;
    QLabel* errorLabel;

private slots:
    void wantToAccept();

signals:

};


#endif // CREATECOMPONENTDIALOG_H
