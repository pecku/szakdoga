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
    void createProcedure(QString name, ProcedureType type, QMap<Method,QString> methods, QMap<QString,QString> members);
    void createEnumerator(QString name, EnumeratorType type, QMap<Method,QString> methods, QMap<QString,QString> members);
    void clear(){procedures.clear();enumerators.clear();}

private:
    QVector<Procedure*> procedures;
    QVector<Enumerator*> enumerators;

signals:

};

#endif // MODEL_H
