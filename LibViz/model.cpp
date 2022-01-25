#include "model.h"

Model::Model(QObject *parent) : QObject(parent)
{

}

void Model::createProcedure(QString name, ProcedureType type, QMap<Method,QString> methods, QMap<QString,QString> members){
    procedures.push_back(new Procedure(name,type,methods,members));
}
void Model::createEnumerator(QString name, EnumeratorType type, QMap<Method,QString> methods, QMap<QString,QString> members){
    enumerators.push_back(new Enumerator(name,type,methods,members));
}

QString Model::generateSource(){
    QString source;
    QTextStream ts(&source);
    for(Procedure* procedure : procedures){
        ts << Qt::endl << procedure->getSource();
    }
    for(Enumerator* enumerator : enumerators){
        ts << Qt::endl << enumerator->getSource();
    }
    return source;
}
