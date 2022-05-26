#include "model.h"

/*!
 * \brief Constructs a new Model object.
 * 
 * \param parent The parent object.
 */
Model::Model(QObject *parent) : QObject(parent)
{
    lastID = 0;
    projectName = "";
    settings = new QSettings(this);

    loadConfig();

    compileProcess = new QProcess(this);
    connect(compileProcess, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(compileFinished(int,QProcess::ExitStatus)));
    connect(compileProcess, SIGNAL(errorOccurred(QProcess::ProcessError)), this, SLOT(compileError(QProcess::ProcessError)));
}

/*!
 * \brief Creates a component.
 * 
 * \param name The name of the component.
 * \param type The type of the component.
 * \return int The id of the component.
 */
int Model::createComponent(QString name, ComponentType type){
    int componentID = newID();
    components.insert(componentID, new Component(name,type,componentID));
    return componentID;
}

/*!
 * \brief Creates a struct.
 * 
 * \param name The name of the struct.
 * \return int The id of the struct.
 */
int Model::createStruct(QString name){
    int structID = newID();
    structs.insert(structID, new Struct(name, structID));
    return structID;
}

/*!
 * \brief Checks if the given component name is used by another component.
 * 
 * \param name The name to be checked.
 * \return true If the name is already in use.
 * \return false If the name is not in use.
 */
bool Model::isComponentNameUsed(QString name){
    foreach(Component* component, components){
        if(component->getName() == name){
            return true;
        }
    }
    foreach(Struct* _struct, structs){
        if(_struct->getName() == name){
            return true;
        }
    }
    return false;
}

/*!
 * \brief Checks if the given object name is used by another object.
 * 
 * \param objectName The name to be checked.
 * \return true If the name is already in use.
 * \return false If the name is not in use.
 */
bool Model::isObjectNameUsed(QString objectName){
    foreach(Component* component, components){
        if(component->getObjectName() == objectName){
            return true;
        }
    }
    return false;
}

/*!
 * \brief Returns the enumerator's name corresponding to the given id.
 * 
 * \param enumeratorID The id of the enumerator.
 * \return QString The name of the enumerator.
 */
QString Model::getEnumeratorNameById(int enumeratorID){
    if(enumeratorID < 0) return nullptr;
    return components[enumeratorID]->getName();
}

/*!
 * \brief Creates a code block.
 * 
 * \return int The new code block's id.
 */
int Model::createCodeBlock(){
    int codeBlockID = newID();
    codeblocks.insert(codeBlockID, new CodeBlock(codeBlockID));
    return codeBlockID;
}

/*!
 * \brief Creates a member.
 * 
 * \param componentID The id of the component that contains the member.
 * \return int The id of the new member.
 */
int Model::createMember(int componentID){
    int memberID = newID();
    if(components.contains(componentID)){
        components[componentID]->createMember(memberID);
    }else if(structs.contains(componentID)){
        structs[componentID]->createMember(memberID);
    }
    return memberID;
}

/*!
 * \brief Creates a custom method.
 * 
 * \param componentID The id of the component that contains the method.
 * \return int The id of the new method.
 */
int Model::createCustomMethod(int componentID){
    int customMethodID = newID();
    if(components.contains(componentID)){
        components[componentID]->createCustomMethod(customMethodID);
    }else if(structs.contains(componentID)){
        structs[componentID]->createCustomMethod(customMethodID);
    }
    return customMethodID;
}

/*!
 * \brief Modifies a member.
 * 
 * \param componentID The id of the component that contains the member.
 * \param memberID The id of the member.
 * \param type The new type of the member.
 * \param name The new name of the member.
 */
void Model::modifyMember(int componentID, int memberID, QString type, QString name){
    if(components.contains(componentID)){
        components[componentID]->setMember(memberID, type, name);
    }else if(structs.contains(componentID)){
        structs[componentID]->setMember(memberID, type, name);
    }
}

/*!
 * \brief Modifies a custom method.
 * 
 * \param componentID The id of the component that contains the method.
 * \param customMethodID The id of the custom method.
 * \param header The new header of the custom method.
 * \param body The new body of the custom method.
 */
void Model::modifyCustomMethod(int componentID, int customMethodID, QString header, QString body){
    if(components.contains(componentID)){
        components[componentID]->setCustomMethod(customMethodID, header, body);
    }else if(structs.contains(componentID)){
        structs[componentID]->setCustomMethod(customMethodID, header, body);
    }
}

/*!
 * \brief Sets a overrideable methods body.
 * 
 * \param componentID The id of the component that contains the method.
 * \param methodType The type of the method.
 * \param methodBody The new body of the method.
 */
void Model::setMethod(int componentID, MethodType methodType, QString methodBody){
    components[componentID]->setMethod(methodType,methodBody);
}

/*!
 * \brief Deletes a component.
 * 
 * \param componentID The id of the component to be deleted.
 */
void Model::deleteComponent(int componentID){
    components.remove(componentID);
}

/*!
 * \brief Delete a struct.
 * 
 * \param structID The id of the struct to be deleted.
 */
void Model::deleteStruct(int structID){
    structs.remove(structID);
}

/*!
 * \brief Deletes a code block.
 * 
 * \param codeBlockID The id of the code block to be deleted.
 */
void Model::deleteCodeBlock(int codeBlockID){
    codeblocks.remove(codeBlockID);
}

/*!
 * \brief Delete a member.
 * 
 * \param componentID The id of the component that contains the member.
 * \param memberID The id of the member to be deleted.
 */
void Model::deleteMember(int componentID, int memberID){
    if(components.contains(componentID)){
        components[componentID]->deleteMember(memberID);
    }else if(structs.contains(componentID)){
        structs[componentID]->deleteMember(memberID);
    }
}

/*!
 * \brief Delete a custom method.
 * 
 * \param componentID The id of the component that contains the method.
 * \param customMethodID The id of the custom method to be deleted.
 */
void Model::deleteCustomMethod(int componentID, int customMethodID){
    if(components.contains(componentID)){
        components[componentID]->deleteCustomMethod(customMethodID);
    }else if(structs.contains(componentID)){
        structs[componentID]->deleteCustomMethod(customMethodID);
    }
}

/*!
 * \brief Generates the source code of the project.
 * 
 * \return QString The generated source code.
 */
QString Model::generateSource(){
    QString source;
    QTextStream ts(&source);

    ts << "#include <iostream>" << Qt::endl;
    ts << "#include \"library.hpp\"" << Qt::endl << Qt::endl;

    for(int i = 1; i <= lastID; i++){
        if(components.contains(i)){
            ts << replaceReference(components[i]->getSource()) << ";" << Qt::endl << Qt::endl;
        }else if(structs.contains(i)){
            ts << replaceReference(structs[i]->getSource()) << ";" << Qt::endl << Qt::endl;
        }
    }

    ts << generateMainSource();

    dataAccess.writeSource(source);

    return source;
}

/*!
 * \brief Generates the source code for the main function.
 * 
 * \return QString The generated source code.
 */
QString Model::generateMainSource(){
    QString source;
    QTextStream ts(&source);

    ts << "int main(){" << Qt::endl;

    foreach(Component* component, components){
        if(component->getUseInMain()){
            ts << "    " << components[component->getEnumeratorID()]->getSourceForObjectCreation() << Qt::endl;
            ts << "    " << component->getSourceForObjectCreation() << Qt::endl;
        }
    }

    foreach(int id, mainIdOrder){
        if(components.contains(id)){
            Component* component = components[id];
            if(component->getUseInMain()){
                QString ms = component->getSourceForMain();
                QTextStream codeStringStream(&ms);
                while(!codeStringStream.atEnd()){
                    ts << Qt::endl << "    " + codeStringStream.readLine();
                }
            }
        }else if(codeblocks.contains(id)){
            ts << Qt::endl << "    " << codeblocks[id]->getSource();
        }        
    }

    ts << Qt::endl << "}" << Qt::endl;

    return source;
}

/*!
 * \brief Runs the compiled source code.
 * 
 */
void Model::run(){
    compile();
    compileProcess->waitForFinished();
    if(!compileFailed){
        #ifdef Q_OS_WIN
        compileProcess->start("./a.exe");
        #endif
        #ifdef Q_OS_LINUX
        compileProcess->start("./a.out");
        #endif
    }
}

/*!
 * \brief Compiles the project's source code.
 * 
 */
void Model::compile(){
    compileFailed = false;
    if(!compilerPathSet){
        emit compilerPathNotSet();
        emit compileProcessEnded();
        compileFailed = true;
    }else{
        emit wantToGenerateSource();
        compileProcess->start(compilerPath, compilerArguments);
    }
}

/*!
 * \brief Stops the compilation process.
 * 
 */
void Model::stopCompile(){
    compileProcess->kill();
    emit compileProcessEnded();
}

/*!
 * \brief Slot for when the compile process finishes.
 * 
 * \param exitCode The exit code of the process.
 * \param exitStatus The exit status of the process.
 */
void Model::compileFinished(int exitCode, QProcess::ExitStatus exitStatus){
    (void)exitStatus;

    QString output;

    if(exitCode == 0){
        output = QString(compileProcess->readAllStandardOutput());
    }else{
        compileFailed = true;
        output = QString(compileProcess->readAllStandardError());
    }

    emit haveCompileOutput(output);
    emit compileProcessEnded();
}

/*!
 * \brief Slot for when the compile process has an error.
 * 
 * \param error The error of the process.
 */
void Model::compileError(QProcess::ProcessError error){
    (void)error;
    compileFailed = true;
    emit haveCompileOutput(QString(compileProcess->readAllStandardError()));
    emit compileProcessEnded();
}

/*!
 * \brief Sets the compiler path.
 * 
 * \param path The path to the compiler.
 */
void Model::setCompilerPath(QString path){
    compilerPath = path;
    settings->setValue("CompilerPath",path);
    compilerPathSet = true;
}

/*!
 * \brief Sets the compiler arguments.
 * 
 * \param args The arguments of the compiler.
 */
void Model::setCompilerArguments(QString args){
    compilerArguments = args.split(" ");
    compilerArguments.prepend("main.cpp");
    compilerArguments.removeAll("");
    settings->setValue("CompilerArguments",args);
}

/*!
 * \brief Loads the application settings.
 * 
 */
void Model::loadConfig(){
    compilerPath = settings->value("CompilerPath", "").toString();
    compilerArguments = settings->value("CompilerArguments", "").toStringList();
    compilerArguments.prepend("main.cpp");
    compilerArguments.removeAll("");
    if(compilerPath == ""){
        compilerPathSet = false;
    }else{
        compilerPathSet = true;
    }
}

/*!
 * \brief Sets the enumerator of a procedure.
 * 
 * \param componentID The id of the component that uses the enumerator.
 * \param enumeratorID The id of the enumerator.
 */
void Model::setEnumerator(int componentID, int enumeratorID){
    components[componentID]->setEnumerator(enumeratorID, components[enumeratorID]->getObjectName());
}

/*!
 * \brief Sets the object name of a component.
 * 
 * \param componentID The id of the component that needs to be modified.
 * \param objectName The new object name.
 */
void Model::setObjectName(int componentID, QString objectName){
    Component* component = components[componentID];
    component->setObjectName(objectName);

    if(component->getType() == DEFAULT || component->getType() == ARRAY || component->getType() == INTERVAL || component->getType() == STRINGSTREAM || component->getType() == SEQINFILE){
        foreach(Component* c, components){
            c->setEnumerator(componentID, objectName);
        }
    }
}

/*!
 * \brief Replaces the references in a source code snippet with the source code of the referenced object.
 * 
 * \param codeString The code snippet that may contain a reference.
 * \return QString The code snippet with the references replaced.
 */
QString Model::replaceReference(QString codeString){
    QString result;
    QTextStream resultStream(&result);
    QTextStream codeStringStream(&codeString);
    while(!codeStringStream.atEnd()){
        const QString currentLine = codeStringStream.readLine();
        QString trimmed = currentLine.trimmed();
        QString replaced;
        if(trimmed.startsWith('%') && trimmed.endsWith('%')){
            trimmed.remove('%');
            replaced = getReferenceSource(trimmed);
            if(replaced == ""){
                replaced = currentLine;
            }
        }else{
            replaced = currentLine;
        }

        resultStream << replaced << Qt::endl;
    }
    return result.trimmed();
}

/*!
 * \brief Generates the source code of a referenced object.
 * 
 * \param objectName The name of the object that is referenced.
 * \return QString The source code of the referenced object.
 */
QString Model::getReferenceSource(QString objectName){
    foreach(Component* component, components){
        if(component->getObjectName() == objectName){
            QString result;
            QTextStream resultStream(&result);
            QString ms = component->getSourceForMain();
            QTextStream codeStringStream(&ms);
            resultStream << "        " + components[component->getEnumeratorID()]->getSourceForObjectCreation() << Qt::endl;
            resultStream << "        " + component->getSourceForObjectCreation();
            while(!codeStringStream.atEnd()){
                resultStream << Qt::endl << "        " + codeStringStream.readLine();
            }
            return result;
        }
    }
    return "";
}

/*!
 * \brief Saves the project.
 * 
 * \return true If the project was saved successfully.
 * \return false If the project has not been saved.
 */
bool Model::saveProject(){
    if(projectName == ""){
        emit needProjectNameForSave();
        if(projectName == "") return false;
    }
    return dataAccess.saveProject(SaveData(projectName,components,codeblocks,structs,mainIdOrder,lastID));
}

/*!
 * \brief Creates a new project.
 * 
 * \return true If the project was created successfully.
 * \return false If the project has not been created.
 */
bool Model::newProject(){
    QString previousProjectName = projectName;
    emit needProjectNameForSave();
    if(projectName == "" || previousProjectName == projectName) return false;
    components.clear();
    codeblocks.clear();
    structs.clear();
    mainIdOrder.clear();
    lastID = 0;
    emit cleared();
    return true;
}

/*!
 * \brief Loads a project.
 * 
 */
void Model::openProject(){
    emit needProjectNameForOpen();
    if(projectName == "") return;
    SaveData loadData = dataAccess.loadProject(projectName);
    components = loadData.components;
    codeblocks = loadData.codeblocks;
    structs = loadData.structs;
    mainIdOrder = loadData.mainIdOrder;
    lastID = loadData.lastID;
    emit projectLoaded(loadData);
}
