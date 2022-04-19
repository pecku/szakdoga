#include "popuptextedit.h"

PopUpTextEdit::PopUpTextEdit(){
    inputDialog = new TextInputDialog();
    connect(inputDialog,SIGNAL(accepted()),this,SLOT(getTextFromInputDialog()));
}

void PopUpTextEdit::focusInEvent(QFocusEvent *e) {
    (void)e;
    clearFocus();
    inputDialog->exec(this->toPlainText());
}

void PopUpTextEdit::getTextFromInputDialog(){
    setText(inputDialog->getText());
    emit textChanged();
}
