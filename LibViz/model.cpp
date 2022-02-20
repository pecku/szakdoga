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

int Model::createMember(int componentID){
    int memberID = newID();
    components[componentID]->createMember(memberID);
    return memberID;
}

void Model::modifyMember(int componentID, int memberID, QString type, QString name){
    components[componentID]->setMember(memberID, type, name);
}

void Model::deleteMember(int componentID, int memberID){
    components[componentID]->deleteMember(memberID);
}

QString Model::generateSource(){
    QString source;
    QTextStream ts(&source);
    foreach(Component* component, components){
        ts << component->getSource() << Qt::endl << Qt::endl;
    }
    return source;
}

void Model::compile(){
    if(!compilerPathSet){
        emit compilerPathNotSet();
        return;
    }

    if(compileProcess->state() == QProcess::Running || compileProcess->state() == QProcess::Starting){
        compileProcess->kill();
    }

    compileProcess->start(compilerPath, compilerArguments);

    connect(compileProcess, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(compileFinished()));
}

void Model::compileFinished(){
    QString output;

    if(compileProcess->exitCode()){
        output = QString(compileProcess->readAllStandardError());
    }else{
        output = QString(compileProcess->readAllStandardOutput());
    }

    compileOutput = output;

    emit haveCompileOutput();
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
    compilerPathSet = true;
}
