#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include "modelkit.h"

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);

    QString generateSource();
    int createComponent(QString name, ComponentType type);
    int createMember(int componentID);
    void modifyMember(int componentID, int memberID, QString type, QString name);
    void deleteMember(int componentID, int memberID);

    void setItem(int componentID, QString item){components[componentID]->setItem(item);}
    void setValue(int componentID, QString value){components[componentID]->setValue(value);}
    void setOptimist(int componentID, bool optimist){components[componentID]->setOptimist(optimist);}
    void setCompare(int componentID, QString compare){components[componentID]->setCompare(compare);}
    void setEnumerator(int componentID, QString enumeratorName){components[componentID]->setEnumerator(enumeratorName);}
    void setMethod(int componentID, MethodType methodType, QString methodBody){components[componentID]->setMethod(methodType,methodBody);}

private:
    QMap<int,Component*> components;
    int lastID;

    int newID() {return ++lastID;}

signals:

};

#endif // MODEL_H
