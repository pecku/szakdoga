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

static const QMap<MethodType,QString> methodTypeStrings = {
    {DESTRUCTOR, "destructor"},
    {NEUTRAL, "neutral"},
    {ADD, "add"},
    {FUNC, "func"},
    {COND, "cond"},
    {FIRST, "first"},
    {WHILECOND, "whilecond"},
    {NEXT, "next"},
    {END, "end"},
    {CURRENT, "current"}
};

static const QMap<QString,MethodType> methodTypeFromString = {
    {methodTypeStrings[DESTRUCTOR], DESTRUCTOR},
    {methodTypeStrings[NEUTRAL], NEUTRAL},
    {methodTypeStrings[ADD], ADD},
    {methodTypeStrings[FUNC], FUNC},
    {methodTypeStrings[COND], COND},
    {methodTypeStrings[FIRST], FIRST},
    {methodTypeStrings[WHILECOND], WHILECOND},
    {methodTypeStrings[NEXT], NEXT},
    {methodTypeStrings[END], END},
    {methodTypeStrings[CURRENT], CURRENT}
};

static const QMap<QString,ComponentType> componentTypeFromString = {
    {componentTypeNameStrings[COUNTING], COUNTING},
    {componentTypeNameStrings[LINSEARCH], LINSEARCH},
    {componentTypeNameStrings[MAXSEARCH], MAXSEARCH},
    {componentTypeNameStrings[SELECTION], SELECTION},
    {componentTypeNameStrings[SUMMATION], SUMMATION},
    {componentTypeNameStrings[DEFAULT], DEFAULT},
    {componentTypeNameStrings[ARRAY], ARRAY},
    {componentTypeNameStrings[INTERVAL], INTERVAL},
    {componentTypeNameStrings[STRINGSTREAM], STRINGSTREAM},
    {componentTypeNameStrings[SEQINFILE], SEQINFILE}
};

struct Member{
    int id;
    QString type;
    QString name;
    Member(){}
    Member(int id) : id(id), type(""), name(""){}
    Member(QString type, QString name) : type(type), name(name){}
};

struct CustomMethod{
    QString header;
    QString body;
    int id;
    CustomMethod(){}
    CustomMethod(int id) : header(""), body(""), id(id) {}
    CustomMethod(QString header, QString body) : header(header), body(body){}
};

class Component{
private:
    QString name;
    int id;
    bool useInMain;
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
    Component(QString name, ComponentType type, int id);

    QString getSource() const;
    QString getSourceForMain() const;
    QString getSourceForObjectCreation() const;
    QString getName() const {return name;}
    int getID() const {return id;}
    bool getUseInMain() const {return useInMain;}
    QString getObjectName() const {return objectName;}
    ComponentType getType() const {return type;}
    QString getItem() const {return item;}
    int getEnumeratorID() const {return enumeratorID;}
    QString getEnumeratorObjectName() const {return enumeratorObjectName;}
    bool getOptimist() const {return optimist;}
    QString getValue() const {return value;}
    QString getCompare() const {return compare;}
    QMap<MethodType,QString> getMethods() const {return methods;}
    QMap<int,Member> getMembers() const {return members;}
    QMap<int,CustomMethod> getCustomMethods() const {return customMethods;}

    void setUseInMain(bool useInMain){this->useInMain = useInMain;}
    void setObjectName(QString objectName){this->objectName = objectName;}
    void setItem(QString item){this->item = item;}
    void setValue(QString value){this->value = value;}
    void setOptimist(bool optimist){this->optimist = optimist;}
    void setCompare(QString compare){this->compare = compare;}
    void setEnumerator(int enumeratorID, QString enumeratorObjectName);
    void setMethod(MethodType methodType, QString methodBody){methods[methodType] = methodBody;}
    void setMember(int id, QString type, QString name){members[id].type = type; members[id].name = name;}
    void createMember(int id){members[id] = Member(id);}
    void deleteMember(int id){members.remove(id);}
    void setCustomMethod(int id, QString header, QString body){customMethods[id].header = header; customMethods[id].body = body;}
    void createCustomMethod(int id){customMethods[id] = CustomMethod(id);}
    void deleteCustomMethod(int id){customMethods.remove(id);}
    void setMethods(QMap<MethodType,QString> methods){this->methods = methods;}
    void setMembers(QMap<int,Member> members){this->members = members;}
    void setCustomMethods(QMap<int,CustomMethod> customMethods){this->customMethods = customMethods;}
};

class CodeBlock{
private:
    int id;
    QString code = "";
public:
    CodeBlock(int id) : id(id){}

    QString getSource(){return code;}
    int getID() const {return id;}
    QString getCode(){return code;}

    void setCode(QString code){this->code = code;}
};

class Struct{
private:
    QString name;
    int id;
    QMap<int,Member> members;
    QMap<int,CustomMethod> customMethods;
public:
    Struct(QString name, int id) : name(name), id(id){}

    QString getSource();
    QString getName() const {return name;}
    int getID() const {return id;}
    QMap<int,Member> getMembers() const {return members;}
    QMap<int,CustomMethod> getCustomMethods() const {return customMethods;}

    void setMember(int id, QString type, QString name){members[id].type = type; members[id].name = name;}
    void createMember(int id){members[id] = Member(id);}
    void deleteMember(int id){members.remove(id);}
    void setCustomMethod(int id, QString header, QString body){customMethods[id].header = header; customMethods[id].body = body;}
    void createCustomMethod(int id){customMethods[id] = CustomMethod(id);}
    void deleteCustomMethod(int id){customMethods.remove(id);}
    void setMembers(QMap<int,Member> members){this->members = members;}
    void setCustomMethods(QMap<int,CustomMethod> customMethods){this->customMethods = customMethods;}
};

struct SaveData{
    QString projectName;
    QMap<int,Component*> components;
    QMap<int,CodeBlock*> codeblocks;
    QMap<int,Struct*> structs;
    QVector<int> mainIdOrder;
    int lastID;
    SaveData(const QString projectName, const QMap<int,Component*> components,
             const QMap<int,CodeBlock*> codeblocks, const QMap<int,Struct*> structs, const QVector<int> mainIdOrder,
             const int lastID)
             : projectName(projectName), components(components),
               codeblocks(codeblocks), structs(structs), mainIdOrder(mainIdOrder), lastID(lastID){}
};

#endif // MODELKIT_H
