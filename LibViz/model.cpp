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

void Model::deleteCodeBlock(int codeBlockID){
    codeblocks.remove(codeBlockID);
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

    dataAccess.writeSource(source);

    return source;
}

#include <QDebug>
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
}
