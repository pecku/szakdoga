#ifndef MODELKIT_H
#define MODELKIT_H

#include <QMap>
#include <QString>
#include <QTextStream>

enum ProcedureType{COUNTING, LINSEARCH, MAXSEARCH, SELECTION, SUMMATION};
enum EnumeratorType{DEFAULT, ARRAY, INTERVAL, STRINGSTREAM, SEQINFILE};
enum Method{DESTRUCTOR, NEUTRAL, ADD, FUNC, COND, FIRST, WHILECOND, NEXT, END, CURRENT};

static const QMap<ProcedureType,QString> procedureTypeNameStrings = {
    {COUNTING, "Counting"},
    {LINSEARCH, "LinSearch"},
    {MAXSEARCH, "MaxSearch"},
    {SELECTION, "Selection"},
    {SUMMATION, "Summation"}
};

static const QMap<EnumeratorType,QString> enumeratorTypeNameStrings = {
    {DEFAULT, "Enumerator"},
    {ARRAY, "ArrayEnumerator"},
    {INTERVAL, "IntervalEnumerator"},
    {STRINGSTREAM, "StringStreamEnumerator"},
    {SEQINFILE, "SeqInFileEnumerator"}
};

static const QMap<Method,QString> methodNameStrings = {
    {DESTRUCTOR, "destructor()"},
    {NEUTRAL, "neutral()"},
    {ADD, "add()"},
    {FUNC, "func()"},
    {COND, "cond()"},
    {FIRST, "first()"},
    {WHILECOND, "whileCond()"},
    {NEXT, "next()"},
    {END, "end()"},
    {CURRENT, "current()"}
};

class Procedure{
private:
    QString name;
    ProcedureType type;
    QMap<Method,QString> methods;
    QMap<QString,QString> members;
public:
    Procedure(QString name, ProcedureType type, QMap<Method,QString> methods, QMap<QString, QString> members) : name(name), type(type), methods(methods), members(members){}
    QString getSource(){
        QString source;
        QTextStream ts(&source);
        ts << name << " " << procedureTypeNameStrings[type];
        for(QString key : members.keys()){
            ts << Qt::endl << key << " " <<  members[key];
        }
        for(Method key : methods.keys()){
            ts << Qt::endl << methodNameStrings[key] << " " << methods[key];
        }
        return source;
    }
};

class Enumerator{
private:
    QString name;
    EnumeratorType type;
    QMap<Method,QString> methods;
    QMap<QString,QString> members;
public:
    Enumerator(QString name, EnumeratorType type, QMap<Method,QString> methods, QMap<QString, QString> members) : name(name), type(type), methods(methods), members(members){}
    QString getSource(){
        QString source;
        QTextStream ts(&source);
        ts << name << " " << enumeratorTypeNameStrings[type];
        for(QString key : members.keys()){
            ts << Qt::endl << key << " " <<  members[key];
        }
        for(Method key : methods.keys()){
            ts << Qt::endl << methodNameStrings[key] << " " << methods[key];
        }
        return source;
    }
};

#endif // MODELKIT_H
