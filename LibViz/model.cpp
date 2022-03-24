#include "model.h"

Model::Model(QObject *parent) : QObject(parent)
{
    lastID = 0;

    loadConfig();

    compileProcess = new QProcess(this);
    connect(compileProcess, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(compileFinished(int,QProcess::ExitStatus)));
    connect(compileProcess, SIGNAL(errorOccurred(QProcess::ProcessError)), this, SLOT(compileError(QProcess::ProcessError)));
}

int Model::createComponent(QString name, ComponentType type){
    int componentID = newID();
    components.insert(componentID, new Component(name,type));
    return componentID;
}

int Model::createStruct(QString name){
    int structID = newID();
    structs.insert(structID, new Struct(name));
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

int Model::createCodeBlock(){
    int codeBlockID = newID();
    codeblocks.insert(codeBlockID, new CodeBlock());
    return codeBlockID;
}

int Model::createMember(int componentID){
    int memberID = newID();
    if(components.contains(componentID)){
        components[componentID]->createMember(memberID);
    }else{
        structs[componentID]->createMember(memberID);
    }
    return memberID;
}

int Model::createCustomMethod(int componentID){
    int customMethodID = newID();
    if(components.contains(componentID)){
        components[componentID]->createCustomMethod(customMethodID);
    }else{
        structs[componentID]->createCustomMethod(customMethodID);
    }
    return customMethodID;
}

void Model::modifyMember(int componentID, int memberID, QString type, QString name){
    if(components.contains(componentID)){
        components[componentID]->setMember(memberID, type, name);
    }else{
        structs[componentID]->setMember(memberID, type, name);
    }
}

void Model::modifyCustomMethod(int componentID, int customMethodID, QString header, QString body){
    if(components.contains(componentID)){
        components[componentID]->setCustomMethod(customMethodID, header, body);
    }else{
        structs[componentID]->setCustomMethod(customMethodID, header, body);
    }
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
    }else{
        structs[componentID]->deleteMember(memberID);
    }
}

void Model::deleteCustomMethod(int componentID, int customMethodID){
    if(components.contains(componentID)){
        components[componentID]->deleteCustomMethod(customMethodID);
    }else{
        structs[componentID]->deleteCustomMethod(customMethodID);
    }
}

QString Model::generateSource(){
    QString source;
    QTextStream ts(&source);

    ts << "#include <iostream>" << Qt::endl << Qt::endl;

    foreach(Component* component, components){
        ts << component->getSource() << Qt::endl << Qt::endl;
    }

    foreach(Struct* _struct, structs){
        ts << _struct->getSource() << Qt::endl << Qt::endl;
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
        }else{
            ts << codeblocks[id]->getSource();
            ts << ";" << Qt::endl;
        }        
    }

    ts << "}" << Qt::endl;

    return source;
}

void Model::run(){
    compile();
    compileProcess->waitForFinished();
    compileProcess->start("./a.exe");
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
    compilerPathSet = true;
}

void Model::setCompilerArguments(QString args){
    compilerArguments = args.split(" ");
}


void Model::loadConfig(){
    //TODO
    compilerPathSet = false;
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
