#ifndef MODELKIT_H
#define MODELKIT_H

#include <QMap>
#include <QString>
#include <QTextStream>

enum ComponentType{COUNTING, LINSEARCH, MAXSEARCH, SELECTION, SUMMATION, DEFAULT, ARRAY, INTERVAL, STRINGSTREAM, SEQINFILE};
enum MethodType{DESTRUCTOR, NEUTRAL, ADD, FUNC, COND, FIRST, WHILECOND, NEXT, END, CURRENT};

static const QMap<ComponentType,QString> componentTypeNameStrings = {
    {COUNTING, "Counting"},
    {LINSEARCH, "LinSearch"},
    {MAXSEARCH, "MaxSearch"},
    {SELECTION, "Selection"},
    {SUMMATION, "Summation"},
    {DEFAULT, "Enumerator"},
    {ARRAY, "ArrayEnumerator"},
    {INTERVAL, "IntervalEnumerator"},
    {STRINGSTREAM, "StringStreamEnumerator"},
    {SEQINFILE, "SeqInFileEnumerator"}
};

static const QMap<MethodType,QString> methodHeaderStrings = {
    {DESTRUCTOR, "destructor()"},
    {NEUTRAL, "neutral()"},
    {ADD, "add()"},
    {FUNC, "func()"},
    {COND, "bool cond()"},
    {FIRST, "void first()"},
    {WHILECOND, "bool whileCond()"},
    {NEXT, "void next()"},
    {END, "bool end()"},
    {CURRENT, "current()"}
};

struct Member{
    QString type;
    QString name;
    Member(){type = ""; name = "";}
    Member(QString type, QString name) : type(type), name(name){}
};

class Component{
private:
    QString name;
    ComponentType type;
    QString item;
    QString enor;
    bool optimist;
    QString value;
    QString compare;
    QMap<MethodType,QString> methods;
    QMap<int,Member> members;
public:
    Component(QString name, ComponentType type);

    QString getSource();

    void setItem(QString item){this->item = item;}
    void setValue(QString value){this->value = value;}
    void setOptimist(bool optimist){this->optimist = optimist;}
    void setCompare(QString compare){this->compare = compare;}
    void setEnumerator(QString enumeratorName){this->enor = enumeratorName;}
    void setMethod(MethodType methodType, QString methodBody){methods[methodType] = methodBody;}
    void setMember(int id, QString type, QString name){members[id].type = type; members[id].name = name;}
    void createMember(int id){members[id] = Member();}
    void deleteMember(int id){members.remove(id);}
};

#endif // MODELKIT_H
