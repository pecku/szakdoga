#include "popuptextedit.h"

PopUpTextEdit::PopUpTextEdit(){
    inputDialog = new TextInputDialog();
    customMethod = true;
    connect(inputDialog,SIGNAL(accepted()),this,SLOT(getTextFromInputDialog()));
}

PopUpTextEdit::PopUpTextEdit(MethodType methodType) : PopUpTextEdit(){
    customMethod = false;
    this->methodType=methodType;
}

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

void PopUpTextEdit::getTextFromInputDialog(){
    setText(inputDialog->getText());
    emit textChanged();
}
