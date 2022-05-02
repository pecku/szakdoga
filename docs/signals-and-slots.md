ComponentWidget
| küldő | signal | fogadó | slot |
|-------|--------|--------|------|
| addnewmemberbutton | clicked() | nézet:ComponentWidget | onAddNewMemberClicked() |
| addnewcustommethodbutton | clicked() | nézet:ComponentWidget | onAddNewMethodClicked() |
| objectNameLineEdit | editingFinished() | nézet:ComponentWidget | objectNameChanged() |
| itemTypeLineEdit | editingFinished() | nézet:ComponentWidget | itemTypeChanged() |
| destructorTextEdit | textChanged() | nézet:ComponentWidget | popUpTextChanged() |
| member | edited() | nézet:ComponentWidget | memberChanged() |
| member | deleteMe() | nézet:ComponentWidget | deleteMember() |
| customMethod | edited() | nézet:ComponentWidget | methodChanged() |
| customMethod | deleteMe() | nézet:ComponentWidget | deleteMethod() |

CreateComponentDialog
| küldő | signal | fogadó | slot |
|-------|--------|--------|------|
| okButton | clicked() | nézet:CreateComponentDialog | wantToAccept() |
| cancelButton | clicked() | nézet:CreateComponentDialog | reject() |

CustomMethodWidget
| küldő | signal | fogadó | slot |
|-------|--------|--------|------|
| headerLineEdit | editingFinished() | nézet:CustomMethodWidget | edited() |
| bodyPopUpTextEdit | textChanged() | nézet:CustomMethodWidget | edited() |
| deleteButton | clicked() | nézet:CustomMethodWidget | deleteMe() |

EnumeratorWidget
| küldő | signal | fogadó | slot |
|-------|--------|--------|------|
| firstTextEdit | textChanged() | nézet:EnumeratorWidget | popUpTextChanged() |
| nextTextEdit | textChanged() | nézet:EnumeratorWidget | popUpTextChanged() |
| endTextEdit | textChanged() | nézet:EnumeratorWidget | popUpTextChanged() |
| currentTextEdit | textChanged() | nézet:EnumeratorWidget | popUpTextChanged() |

MainWindow
| küldő | signal | fogadó | slot |
|-------|--------|--------|------|
| model | haveCompileOutput(QString) | nézet:MainWindow | showCompileOutput(QString) |
| model | compileProcessEnded() | nézet:MainWindow | allowCompile() |
| model | compilerPathNotSet() | nézet:MainWindow | showCompilerPathWarning() |
| model | needProjectNameForSave() | nézet:MainWindow | showProjectSaveDialog() |
| model | needProjectNameForOpen() | nézet:MainWindow | showProjectOpenDialog() |
| model | projectLoaded(SaveData) | nézet:MainWindow | refresh(SaveData) |
| model | cleared() | nézet:MainWindow | clear() |
| listWidget | itemChanged(QListWidgetItem*) | nézet:MainWindow | listItemChanged(QListWidgetItem*) |
| createComponentDialog | accepted() | nézet:MainWindow | createComponent() |
| settingsDialog | accepted() | nézet:MainWindow | updateSettings() |
| createComponentAction | triggered() | nézet:MainWindow | showCreateComponentDialog() |
| deleteComponentAction | triggered() | nézet:MainWindow | deleteComponent() |
| deleteListItemAction | triggered() | nézet:MainWindow | deleteListItem() |
| createCodeBlockAction | triggered() | nézet:MainWindow | createCodeBlock() |
| generateAction | triggered() | nézet:MainWindow | generateSource() |
| runAction | triggered() | nézet:MainWindow | modelRun() |
| buildAction | triggered() | nézet:MainWindow | modelCompile() |
| stopCompileAction | triggered() | nézet:MainWindow | modelStopCompile() |
| settingsAction | triggered() | nézet:MainWindow | showSettingsDialog() |
| newProjectAction | triggered() | nézet:MainWindow | newProject() |
| loadProjectAction | triggered() | nézet:MainWindow | loadProject() |
| saveProjectAction | triggered() | nézet:MainWindow | saveProject() |
| listWidget | itemSelectionChanged() | nézet:MainWindow | changeSelectedComponent() |

MemberWidget
| küldő | signal | fogadó | slot |
|-------|--------|--------|------|
| typeLineEdit | editingFinished() | nézet:MemberWidget | edited() |
| nameLineEdit | editingFinished() | nézet:MemberWidget | edited() |
| deleteButton | clicked() | nézet:MemberWidget | deleteMe() |

model::compileProcess
| küldő | signal | fogadó | slot |
|-------|--------|--------|------|
| compileProcess | finished(int,QProcess::ExitStatus) | modell | compileFinished(int,QProcess::ExitStatus) |
| compileProcess | errorOccurred(QProcess::ProcessError) | modell | compileError(QProcess::ProcessError) |

PopUpTextEdit
| küldő | signal | fogadó | slot |
|-------|--------|--------|------|
| inputDialog | accepted() | nézet:PopUpTextEdit | getTextFromInputDialog() |

ProcedureWidget
| küldő | signal | fogadó | slot |
|-------|--------|--------|------|
| enorComboBox | currentIndexChanged(int) | nézet:ProcedureWidget | enorChanged(int) |
| optimistCheckBox | stateChanged(int) | nézet:ProcedureWidget | optimistChanged() |
| valueLineEdit | editingFinished() | nézet:ProcedureWidget | valueChanged() |
| greaterRadioButton | toggled(bool) | nézet:ProcedureWidget | compareChanged() |
| neutralTextEdit | textChanged() | nézet:ProcedureWidget | popUpTextChanged() |
| addTextEdit | textChanged() | nézet:ProcedureWidget | popUpTextChanged() |
| funcTextEdit | textChanged() | nézet:ProcedureWidget | popUpTextChanged() |
| condTextEdit | textChanged() | nézet:ProcedureWidget | popUpTextChanged() |
| firstTextEdit | textChanged() | nézet:ProcedureWidget | popUpTextChanged() |
| whileCondTextEdit | textChanged() | nézet:ProcedureWidget | popUpTextChanged() |

SettingsDialog
| küldő | signal | fogadó | slot |
|-------|--------|--------|------|
| okButton | clicked() | nézet:SettingsDialog | accept() |
| cancelButton | clicked() | nézet:SettingsDialog | reject() |

StructWidget
| küldő | signal | fogadó | slot |
|-------|--------|--------|------|
| addnewmemberbutton | clicked() | nézet:StructWidget | onAddNewMemberClicked() |
| addnewcustommethodbutton | clicked() | nézet:StructWidget | onAddNewMethodClicked() |
| member | edited() | nézet:StructWidget | memberChanged() |
| member | deleteMe() | nézet:StructWidget | deleteMember() |
| customMethod | edited() | nézet:StructWidget | methodChanged() |
| customMethod | deleteMe() | nézet:StructWidget | deleteMethod() |

TextInputDialog
| küldő | signal | fogadó | slot |
|-------|--------|--------|------|
| saveButton | clicked() | nézet:TextInputDialog | accept() |
| cancelButton | clicked() | nézet:TextInputDialog | reject() |