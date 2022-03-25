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

static const QMap<MethodType,QPair<QString,QString>> methodHeaderStrings = {
    {DESTRUCTOR, QPair<QString,QString>("(",")")},
    {NEUTRAL, QPair<QString,QString>("neutral(",") const")},
    {ADD, QPair<QString,QString>("add(",") const")},
    {FUNC, QPair<QString,QString>("func(",") const")},
    {COND, QPair<QString,QString>("bool cond(",") const")},
    {FIRST, QPair<QString,QString>("void first(",")")},
    {WHILECOND, QPair<QString,QString>("bool whileCond(",") const")},
    {NEXT, QPair<QString,QString>("void next(",")")},
    {END, QPair<QString,QString>("bool end(",") const")},
    {CURRENT, QPair<QString,QString>("current(",") const")}
};

struct Member{
    QString type;
    QString name;
    Member(){type = ""; name = "";}
    Member(QString type, QString name) : type(type), name(name){}
};

struct CustomMethod{
    QString header;
    QString body;
    CustomMethod(){header = ""; body = "";}
    CustomMethod(QString header, QString body) : header(header), body(body){}
};

class Component{
    friend class Main;
private:
    QString name;
    QString objectName;
    ComponentType type;
    QString item;
    int enumeratorID;
    QString enumeratorObjectName;
    bool optimist;
    QString value;
    QString compare;
    QMap<MethodType,QString> methods;
    QMap<int,Member> members;
    QMap<int,CustomMethod> customMethods;
public:
    Component(QString name, ComponentType type);

    QString getSource();
    QString getSourceForMain();
    QString getSourceForObjectCreation();
    QString getObjectName(){return objectName;}
    QString getName(){return name;}
    ComponentType getType(){return type;}

    void setObjectName(QString objectName){this->objectName = objectName;}
    void setItem(QString item){this->item = item;}
    void setValue(QString value){this->value = value;}
    void setOptimist(bool optimist){this->optimist = optimist;}
    void setCompare(QString compare){this->compare = compare;}
    void setEnumerator(int enumeratorID, QString enumeratorObjectName);
    void setMethod(MethodType methodType, QString methodBody){methods[methodType] = methodBody;}
    void setMember(int id, QString type, QString name){members[id].type = type; members[id].name = name;}
    void createMember(int id){members[id] = Member();}
    void deleteMember(int id){members.remove(id);}
    void setCustomMethod(int id, QString header, QString body){customMethods[id].header = header; customMethods[id].body = body;}
    void createCustomMethod(int id){customMethods[id] = CustomMethod();}
    void deleteCustomMethod(int id){customMethods.remove(id);}
};

class CodeBlock{
private:
    QString code = "";
public:
    QString getSource(){return code;}
    void setCode(QString code){this->code = code;}
};

class Struct{
private:
    QString name;
    QMap<int,Member> members;
    QMap<int,CustomMethod> customMethods;
public:
    Struct(QString name) : name(name){}

    QString getSource();
    QString getName(){return name;}

    void setMember(int id, QString type, QString name){members[id].type = type; members[id].name = name;}
    void createMember(int id){members[id] = Member();}
    void deleteMember(int id){members.remove(id);}
    void setCustomMethod(int id, QString header, QString body){customMethods[id].header = header; customMethods[id].body = body;}
    void createCustomMethod(int id){customMethods[id] = CustomMethod();}
    void deleteCustomMethod(int id){customMethods.remove(id);}
};

#endif // MODELKIT_H
