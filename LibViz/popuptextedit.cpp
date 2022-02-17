#include "popuptextedit.h"

PopUpTextEdit::PopUpTextEdit(MethodType methodType) : methodType(methodType){
    inputDialog = new TextInputDialog();
    connect(inputDialog,SIGNAL(accepted()),this,SLOT(getTextFromInputDialog()));
}

void PopUpTextEdit::focusInEvent(QFocusEvent *e) {
    (void)e;
    clearFocus();
    inputDialog->exec();
}

void PopUpTextEdit::getTextFromInputDialog(){
    setText(inputDialog->getText());
    emit textChanged();
}
