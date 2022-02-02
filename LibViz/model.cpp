#include "model.h"

Model::Model(QObject *parent) : QObject(parent)
{
    lastID = 0;
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
        ts << Qt::endl << component->getSource();
    }
    return source;
}
