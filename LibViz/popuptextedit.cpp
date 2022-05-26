#include "popuptextedit.h"

/*!
 * \brief Constructs a new Pop Up Text Edit object.
 * 
 */
PopUpTextEdit::PopUpTextEdit(){
    inputDialog = new TextInputDialog();
    customMethod = true;
    connect(inputDialog,SIGNAL(accepted()),this,SLOT(getTextFromInputDialog()));
}

/*!
 * \brief Constructs a new Pop Up Text Edit object with the given type.
 * 
 * \param methodType The type of the method.
 */
PopUpTextEdit::PopUpTextEdit(MethodType methodType) : PopUpTextEdit(){
    customMethod = false;
    this->methodType=methodType;
}

/*!
 * \brief Event override for opening the text input dialog when the TextEdit gets focus.
 * 
 * \param e 
 */
void PopUpTextEdit::focusInEvent(QFocusEvent *e) {
    (void)e;
    clearFocus();
    if(customMethod){
        inputDialog->setWindowTitle("method");
    }else{
        inputDialog->setWindowTitle(methodTypeStrings[methodType]);
    }
    inputDialog->exec(this->toPlainText());
}

/*!
 * \brief Sets the text to be the same as provided in the input dialog.
 * 
 */
void PopUpTextEdit::getTextFromInputDialog(){
    setText(inputDialog->getText());
    emit textChanged();
}
