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

int Model::createMember(int componentID, QString name, QString value){
    int memberID = newID();
    components[componentID]->setMember(memberID, name, value);
    return memberID;
}

void Model::modifyMember(int componentID, int memberID, QString name, QString value){
    components[componentID]->setMember(memberID, name, value);
}

QString Model::generateSource(){
    QString source;
    QTextStream ts(&source);
    foreach(Component* component, components){
        ts << Qt::endl << component->getSource();
    }
    return source;
}
