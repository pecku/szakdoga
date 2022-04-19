#include "model.h"

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

int Model::createComponent(QString name, ComponentType type){
    int componentID = newID();
    components.insert(componentID, new Component(name,type,componentID));
    return componentID;
}

int Model::createStruct(QString name){
    int structID = newID();
    structs.insert(structID, new Struct(name, structID));
    return structID;
}

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

bool Model::isObjectNameUsed(QString objectName){
    foreach(Component* component, components){
        if(component->getObjectName() == objectName){
            return true;
        }
    }
    return false;
}

QString Model::getEnumeratorNameById(int enumeratorID){
    return components[enumeratorID]->getName();
}

int Model::createCodeBlock(){
    int codeBlockID = newID();
    codeblocks.insert(codeBlockID, new CodeBlock(codeBlockID));
    return codeBlockID;
}

int Model::createMember(int componentID){
    int memberID = newID();
    if(components.contains(componentID)){
        components[componentID]->createMember(memberID);
    }else if(structs.contains(componentID)){
        structs[componentID]->createMember(memberID);
    }
    return memberID;
}

int Model::createCustomMethod(int componentID){
    int customMethodID = newID();
    if(components.contains(componentID)){
        components[componentID]->createCustomMethod(customMethodID);
    }else if(structs.contains(componentID)){
        structs[componentID]->createCustomMethod(customMethodID);
    }
    return customMethodID;
}

void Model::modifyMember(int componentID, int memberID, QString type, QString name){
    if(components.contains(componentID)){
        components[componentID]->setMember(memberID, type, name);
    }else if(structs.contains(componentID)){
        structs[componentID]->setMember(memberID, type, name);
    }
}

void Model::modifyCustomMethod(int componentID, int customMethodID, QString header, QString body){
    if(components.contains(componentID)){
        components[componentID]->setCustomMethod(customMethodID, header, body);
    }else if(structs.contains(componentID)){
        structs[componentID]->setCustomMethod(customMethodID, header, body);
    }
}

void Model::setMethod(int componentID, MethodType methodType, QString methodBody){
    components[componentID]->setMethod(methodType,methodBody);
}

void Model::deleteComponent(int componentID){
    components.remove(componentID);
}

void Model::deleteStruct(int structID){
    structs.remove(structID);
}

void Model::deleteCodeBlock(int codeBlockID){
    codeblocks.remove(codeBlockID);
}

void Model::deleteMember(int componentID, int memberID){
    if(components.contains(componentID)){
        components[componentID]->deleteMember(memberID);
    }else if(structs.contains(componentID)){
        structs[componentID]->deleteMember(memberID);
    }
}

void Model::deleteCustomMethod(int componentID, int customMethodID){
    if(components.contains(componentID)){
        components[componentID]->deleteCustomMethod(customMethodID);
    }else if(structs.contains(componentID)){
        structs[componentID]->deleteCustomMethod(customMethodID);
    }
}

QString Model::generateSource(){
    QString source;
    QTextStream ts(&source);

    ts << "#include <iostream>" << Qt::endl;
    ts << "#include \"library.hpp\"" << Qt::endl << Qt::endl;

    foreach(Struct* _struct, structs){
        ts << replaceReference(_struct->getSource()) << ";" << Qt::endl << Qt::endl;
    }

    foreach(Component* component, components){
        ts << replaceReference(component->getSource()) << ";" << Qt::endl << Qt::endl;
    }

    ts << generateMainSource();

    dataAccess.writeSource(source);

    return source;
}

QString Model::generateMainSource(){
    QString source;
    QTextStream ts(&source);

    ts << "int main(){" << Qt::endl;

    foreach(Component* component, components){
        ts << "\t" << component->getSourceForObjectCreation() << Qt::endl;
    }

    foreach(int id, mainIdOrder){
        ts << "\t";
        if(components.contains(id)){
            ts << components[id]->getSourceForMain();
        }else if(codeblocks.contains(id)){
            ts << codeblocks[id]->getSource() << Qt::endl;
        }        
    }

    ts << "}" << Qt::endl;

    return source;
}

void Model::run(){
    compile();
    compileProcess->waitForFinished();
    #ifdef Q_OS_WIN
    compileProcess->start("./a.exe");
    #endif
    #ifdef Q_OS_LINUX
    compileProcess->start("./a.out");
    #endif
}

void Model::compile(){
    if(!compilerPathSet){
        emit compilerPathNotSet();
        emit compileProcessEnded();
    }else{
        compileProcess->start(compilerPath, compilerArguments);
    }
}

void Model::stopCompile(){
    compileProcess->kill();
    emit compileProcessEnded();
}

void Model::compileFinished(int exitCode, QProcess::ExitStatus exitStatus){
    (void)exitStatus;

    QString output;

    if(exitCode == 0){
        output = QString(compileProcess->readAllStandardOutput());
    }else{
        output = QString(compileProcess->readAllStandardError());
    }

    emit haveCompileOutput(output);
    emit compileProcessEnded();
}

void Model::compileError(QProcess::ProcessError error){
    (void)error;
    emit haveCompileOutput(QString(compileProcess->readAllStandardError()));
    emit compileProcessEnded();
}

void Model::setCompilerPath(QString path){
    compilerPath = path;
    settings->setValue("CompilerPath",path);
    compilerPathSet = true;
}

void Model::setCompilerArguments(QString args){
    compilerArguments = args.split(" ");
    settings->setValue("CompilerArguments",args);
}


void Model::loadConfig(){
    compilerPath = settings->value("CompilerPath", "").toString();
    compilerArguments = settings->value("CompilerArguments", "").toStringList();
    if(compilerPath == ""){
        compilerPathSet = false;
    }else{
        compilerPathSet = true;
    }
}

void Model::setEnumerator(int componentID, int enumeratorID){
    components[componentID]->setEnumerator(enumeratorID, components[enumeratorID]->getObjectName());
}

void Model::setObjectName(int componentID, QString objectName){
    Component* component = components[componentID];
    component->setObjectName(objectName);

    if(component->getType() == DEFAULT || component->getType() == ARRAY || component->getType() == INTERVAL || component->getType() == STRINGSTREAM || component->getType() == SEQINFILE){
        foreach(Component* c, components){
            c->setEnumerator(componentID, objectName);
        }
    }
}

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
    return result;
}

QString Model::getReferenceSource(QString objectName){
    foreach(Component* component, components){
        if(component->getObjectName() == objectName){
            return "\t\t" + component->getSourceForObjectCreation() + "\n\t\t" + component->getSourceForMain();
        }
    }
    return "";
}

bool Model::saveProject(){
    if(projectName == ""){
        emit needProjectNameForSave();
        if(projectName == "") return false;
    }
    return dataAccess.saveProject(SaveData(projectName,components,codeblocks,structs,mainIdOrder,lastID));
}

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
