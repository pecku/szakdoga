#include "model.h"

Model::Model(QObject *parent) : QObject(parent)
{
    lastID = 0;

    loadConfig();

    compileProcess = new QProcess(this);
}

int Model::createComponent(QString name, ComponentType type){
    int componentID = newID();
    components.insert(componentID, new Component(name,type));
    return componentID;
}

bool Model::isComponentNameUsed(QString name){
    foreach(Component* component, components){
        if(component->getName() == name){
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
    components[componentID]->createMember(memberID);
    return memberID;
}

void Model::modifyMember(int componentID, int memberID, QString type, QString name){
    components[componentID]->setMember(memberID, type, name);
}

void Model::deleteComponent(int componentID){
    components.remove(componentID);
}

void Model::deleteCodeBlock(int codeBlockID){
    codeblocks.remove(codeBlockID);
}

void Model::deleteMember(int componentID, int memberID){
    components[componentID]->deleteMember(memberID);
}

QString Model::generateSource(){
    QString source;
    QTextStream ts(&source);

    ts << "#include <iostream>" << Qt::endl << Qt::endl;

    foreach(Component* component, components){
        ts << component->getSource() << Qt::endl << Qt::endl;
    }

    ts << generateMainSource();

    dataAccess.writeSource(source);

    return source;
}

QString Model::generateMainSource(){
    QString source;
    QTextStream ts(&source);

    ts << "int main(){" << Qt::endl;

    foreach(int id, mainIdOrder){
        ts << "\t";
        if(components.contains(id)){
            ts << id;
        }else{
            ts << codeblocks[id]->getSource();
        }
        ts << ";" << Qt::endl;
    }

    ts << "}" << Qt::endl;

    return source;
}

void Model::run(){
    compile();
    compileProcess->waitForFinished();
    qDebug()<<"run";
}

void Model::compile(){
    if(!compilerPathSet){
        emit compilerPathNotSet();
        emit compileProcessEnded();
        return;
    }

    compileProcess->kill();
    compileProcess = new QProcess();

    compileProcess->start(compilerPath, compilerArguments);

    connect(compileProcess, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(compileFinished()));
    connect(compileProcess, SIGNAL(errorOccurred(QProcess::ProcessError)), this, SLOT(compileFinished()));
}

void Model::stopCompile(){
    compileProcess->kill();
    compileProcess = new QProcess();
    if(compileProcess->state() == QProcess::NotRunning){
        emit compileProcessEnded();
    }
}

void Model::compileFinished(){
    QString output;

    output = QString(compileProcess->readAllStandardError());
    if(!output.size()) output = compileProcess->errorString();
    if(!output.size()) output = QString(compileProcess->readAllStandardOutput());

    compileOutput = output;

    emit haveCompileOutput();
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
