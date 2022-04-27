## A modell által használt osztályok:

- __Component__: A felhasználó által létrehozott komponens, amely ábrázolhat egy programozási tételt vagy egy felsorolót. A komponens minden adata egy ilyen objektumban tárolódik.
- __CodeBlock__: A felhasználó által létrehozott kódblokk, amely a main függvényben kerül felhasználásra. A kódblokk minden adata egy ilyen objektumban tárolódik.
- __Struct__: A felhasználó által létrehozott struktúra, amely egy programozási tételben használható. A struktúra minden adata egy ilyen objektumban tárolódik.
- __Member__: Egy struktúra, amely a komponensekben szereplő adattagok tárolására hivatott.
- __CustomMethod__: Egy struktúra, amely a komponensekben szereplő saját metódusok tárolására hivatott.
- __SaveData__: Egy struktúra, amely képes minden olyan adatot képes tárolni, amely egy projekt elmentéséhez szükséges.

### Egyéb segédobjektumok:

```cpp
enum ComponentType;
enum MethodType;
static const QMap<ComponentType,QString> componentTypeNameStrings;
static const QMap<MethodType,QPair<QString,QString>> methodHeaderStrings;
static const QMap<MethodType,QString> methodTypeStrings;
static const QMap<QString,MethodType> methodTypeFromString;
static const QMap<QString,ComponentType> componentTypeFromString;
```

- ComponentType: Egy enum, amely a lehetséges komponens típusokat tárolja.
- MethodType: Egy enum, amely a lehetséges metódus típusokat tárolja.
- componentTypeNameStrings: Egy asszociatív tároló, amely segítségével komponens típus alapján visszakapjuk a típus megjeleníthető elnevezését.
- methodHeaderStrings: Egy asszociatív tároló, amely segítségével metódus típus alapján visszakapjuk a metódus fejlécét.
- methodTypeStrings: Egy asszociatív tároló, amely segítségével metódus típus alapján visszakapjuk a metódus típusának megjeleníthető elnevezését.
- methodTypeFromString: Egy asszociatív tároló, amely segítségével metódus elnevezése alapján visszakapjuk a metódus típusát.
- componentTypeFromString: Egy asszociatív tároló, amely segítségével komponens elnevezése alapján visszakapjuk a komponens típusát.


### Component:

adattagjai:
```cpp
QString name;
int id;
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
```

- name: A komponens neve.
- id: A komponens azonosítója.
- objectName: A komponens objektum neve.
- type: A komponens típusa.
- item: A komponens objektumhoz tartozó item típus.
- enumeratorID: A komponens által használt felsoroló azonosítója.
- enumeratorObjectName: A komponens által használt felsoroló objektum neve.
- optimist: A komponens optimista-e.
- value: A omponens value típusát tartalmazza.
- compare: A komponens összehasonlítási módja.
- methods: A komponens felülírt metódusai.
- members: A komponens adattagjai azonosítókkal párosítva.
- customMethods: A komponens saját metódusai azonosítókkal párosítva.


getterei:
```cpp
QString getSource() const;
QString getSourceForMain() const;
QString getSourceForObjectCreation() const;
QString getName() const;
int getID() const;
QString getObjectName() const;
ComponentType getType() const;
QString getItem() const;
int getEnumeratorID() const;
QString getEnumeratorObjectName() const;
bool getOptimist() const;
QString getValue() const;
QString getCompare() const;
QMap<MethodType,QString> getMethods() const;
QMap<int,Member> getMembers() const;
QMap<int,CustomMethod> getCustomMethods() const;
```

setterei:
```cpp
void setObjectName(QString objectName);
void setItem(QString item);
void setValue(QString value);
void setOptimist(bool optimist);
void setCompare(QString compare);
void setEnumerator(int enumeratorID, QString enumeratorObjectName);
void setMethod(MethodType methodType, QString methodBody);
void setMember(int id, QString type, QString name);
void createMember(int id);
void deleteMember(int id);
void setCustomMethod(int id, QString header, QString body);
void createCustomMethod(int id);
void deleteCustomMethod(int id);
void setMethods(QMap<MethodType,QString> methods);
void setMembers(QMap<int,Member> members);
void setCustomMethods(QMap<int,CustomMethod> customMethods);
```

### Struct:

adattagjai:
```cpp
QString name;
int id;
QMap<int,Member> members;
QMap<int,CustomMethod> customMethods;
```

getterei:
```cpp
QString getSource();
QString getName() const {return name;}
int getID() const {return id;}
QMap<int,Member> getMembers() const {return members;}
QMap<int,CustomMethod> getCustomMethods() const {return customMethods;}
```

setterei:
```cpp
void setMember(int id, QString type, QString name);
void createMember(int id);
void deleteMember(int id);
void setCustomMethod(int id, QString header, QString body);
void createCustomMethod(int id);
void deleteCustomMethod(int id);
void setMembers(QMap<int,Member> members);
void setCustomMethods(QMap<int,CustomMethod> customMethods);
```


### CodeBlock:

adattagjai:
```cpp
int id;
QString code = "";
```

getterei:
```cpp
QString getSource(){return code;}
int getID() const {return id;}
QString getCode(){return code;}
```

setterei:
```cpp
void setCode(QString code){this->code = code;}
```


### SaveData:

adattagjai:
```cpp
QString projectName;
QMap<int,Component*> components;
QMap<int,CodeBlock*> codeblocks;
QMap<int,Struct*> structs;
QVector<int> mainIdOrder;
int lastID;
```

- projectName: A projekt neve.
- components: A projektben lévő komponensek tárolója.
- codeblocks: A projektben lévő kódblokkok tárolója.
- structs: A projektben lévő struktúrák tárolója.
- mainIdOrder: A projektben lévő komponensek és kódblokkok main függvénybeli sorrendje.
- lastID: Az utoljára létrehozott egyedi objektum azonosító.

A SaveData konstruktorában minden tárolandó adatot egyben meg lehet adni.


