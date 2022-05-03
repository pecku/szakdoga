A következő táblázatok tartalmazzák a signal-slot kapcsolatokat. Minden táblázat előtt kiemelve szerepel az osztály, amely a signalok fogadója és amelynek a küldő objektumok az adattagjai.

__ComponentWidget__
| küldő | signal | slot |
|-------|--------|------|
| addnewmemberbutton | clicked() | onAddNewMemberClicked() |
| addnewcustommethodbutton | clicked() | onAddNewMethodClicked() |
| objectNameLineEdit | editingFinished() | objectNameChanged() |
| itemTypeLineEdit | editingFinished() | itemTypeChanged() |
| destructorTextEdit | textChanged() | popUpTextChanged() |
| member | edited() | memberChanged() |
| member | deleteMe() | deleteMember() |
| customMethod | edited() | methodChanged() |
| customMethod | deleteMe() | deleteMethod() |

__CreateComponentDialog__
| küldő | signal | slot |
|-------|--------|------|
| okButton | clicked() | wantToAccept() |
| cancelButton | clicked() | reject() |

__CustomMethodWidget__
| küldő | signal | slot |
|-------|--------|------|
| headerLineEdit | editingFinished() | edited() |
| bodyPopUpTextEdit | textChanged() | edited() |
| deleteButton | clicked() | deleteMe() |

__EnumeratorWidget__
| küldő | signal | slot |
|-------|--------|------|
| firstTextEdit | textChanged() | popUpTextChanged() |
| nextTextEdit | textChanged() | popUpTextChanged() |
| endTextEdit | textChanged() | popUpTextChanged() |
| currentTextEdit | textChanged() | popUpTextChanged() |

__MainWindow__
| küldő | signal | slot |
|-------|--------|------|
| model | haveCompileOutput(QString) | showCompileOutput(QString) |
| model | compileProcessEnded() | allowCompile() |
| model | compilerPathNotSet() | showCompilerPathWarning() |
| model | needProjectNameForSave() | showProjectSaveDialog() |
| model | needProjectNameForOpen() | showProjectOpenDialog() |
| model | projectLoaded(SaveData) | refresh(SaveData) |
| model | cleared() | clear() |
| listWidget | itemChanged(QListWidgetItem*) | listItemChanged(QListWidgetItem*) |
| createComponentDialog | accepted() | createComponent() |
| settingsDialog | accepted() | updateSettings() |
| createComponentAction | triggered() | showCreateComponentDialog() |
| deleteComponentAction | triggered() | deleteComponent() |
| deleteListItemAction | triggered() | deleteListItem() |
| createCodeBlockAction | triggered() | createCodeBlock() |
| generateAction | triggered() | generateSource() |
| runAction | triggered() | modelRun() |
| buildAction | triggered() | modelCompile() |
| stopCompileAction | triggered() | modelStopCompile() |
| settingsAction | triggered() | showSettingsDialog() |
| newProjectAction | triggered() | newProject() |
| loadProjectAction | triggered() | loadProject() |
| saveProjectAction | triggered() | saveProject() |
| listWidget | itemClicked(QListWidgetItem*) | changeSelectedComponent() |
| minden procedure | useInMainChecked(QString,int) | addListItem(QString,int) |
| minden procedure | useInMainUnchecked(int) | deleteListItem(int) |

__MemberWidget__
| küldő | signal | slot |
|-------|--------|------|
| typeLineEdit | editingFinished() | edited() |
| nameLineEdit | editingFinished() | edited() |
| deleteButton | clicked() | deleteMe() |

__Model__
| küldő | signal | slot |
|-------|--------|------|
| compileProcess | finished(int,QProcess::ExitStatus) | compileFinished(int,QProcess::ExitStatus) |
| compileProcess | errorOccurred(QProcess::ProcessError) | compileError(QProcess::ProcessError) |

__PopUpTextEdit__
| küldő | signal | slot |
|-------|--------|------|
| inputDialog | accepted() | getTextFromInputDialog() |

__ProcedureWidget__
| küldő | signal | slot |
|-------|--------|------|
| enorComboBox | currentIndexChanged(int) | enorChanged(int) |
| useInMainCheckBox | stateChanged(int) | useInMainChanged() |
| optimistCheckBox | stateChanged(int) | optimistChanged() |
| valueLineEdit | editingFinished() | valueChanged() |
| greaterRadioButton | toggled(bool) | compareChanged() |
| neutralTextEdit | textChanged() | popUpTextChanged() |
| addTextEdit | textChanged() | popUpTextChanged() |
| funcTextEdit | textChanged() | popUpTextChanged() |
| condTextEdit | textChanged() | popUpTextChanged() |
| firstTextEdit | textChanged() | popUpTextChanged() |
| whileCondTextEdit | textChanged() | popUpTextChanged() |

__SettingsDialog__
| küldő | signal | slot |
|-------|--------|------|
| okButton | clicked() | accept() |
| cancelButton | clicked() | reject() |

__StructWidget__
| küldő | signal | slot |
|-------|--------|------|
| addnewmemberbutton | clicked() | onAddNewMemberClicked() |
| addnewcustommethodbutton | clicked() | onAddNewMethodClicked() |
| member | edited() | memberChanged() |
| member | deleteMe() | deleteMember() |
| customMethod | edited() | methodChanged() |
| customMethod | deleteMe() | deleteMethod() |

__TextInputDialog__
| küldő | signal | slot |
|-------|--------|------|
| saveButton | clicked() | accept() |
| cancelButton | clicked() | reject() |
            