#include "modelkit.h"

Component::Component(QString name, ComponentType type, int id) : name(name), id(id), type(type){
    enumeratorID = -1;
    if(type == DEFAULT || type == ARRAY || type == INTERVAL || type == STRINGSTREAM || type == SEQINFILE){
        useInMain = false;
    }else{
        useInMain = true;
    }
}

QString Component::getSource() const{
    QString source;
    QTextStream ts(&source);

    ts << "class " << name << " : public " << componentTypeNameStrings[type];

    ts << "<" << item;

    if(type == LINSEARCH){
        ts << "," << (optimist ? "true" : "false");
    }else if(type == MAXSEARCH){
        ts << "," << value;
        ts << "," << compare;
    }else if(type == SUMMATION){
        ts << "," << value;
    }

    ts << ">";

    ts << Qt::endl << "{";
    ts << Qt::endl << "private:";

    foreach(Member member, members){
        ts << Qt::endl << "    " << member.type << " " <<  member.name << ";";
    }

    ts << Qt::endl << "public:";

    foreach(CustomMethod customMethod, customMethods){
        ts << Qt::endl << "    " << customMethod.header << Qt::endl << "    {";
        QTextStream methodBodyStream(&customMethod.body);
        while(!methodBodyStream.atEnd()){
            ts << Qt::endl << "        " << methodBodyStream.readLine();
        }
        ts << Qt::endl << "    " << "}";
    }

    ts << Qt::endl << "protected:";

    auto methodkeys = methods.keys();
    foreach(MethodType key, methodkeys){
        ts << Qt::endl << "    ";

        if(key == NEUTRAL || key == ADD || key == FUNC){
            ts << value << " ";
        }else if(key == CURRENT){
            ts << item << " ";
        }else if(key == DESTRUCTOR){
            ts << "~" << name;
        }


        ts << methodHeaderStrings[key].first;

        if(key == FUNC || key == COND){
            ts << "const " << item << "& e";
        }else if(key == ADD){
            ts << "const " << value << "& a, " << "const " << value << "& b";
        }else if(key == WHILECOND){
            ts << "const " << item << "& current";
        }

        ts << methodHeaderStrings[key].second << " override" << Qt::endl << "    {";

        QString methodBody = methods[key];
        QTextStream methodBodyStream(&methodBody);
        while(!methodBodyStream.atEnd()){
            ts << Qt::endl << "        " << methodBodyStream.readLine();
        }
        ts << Qt::endl << "    " << "}";
    }
    ts << Qt::endl << "}";

    return source;
}

QString Component::getSourceForObjectCreation() const{
    QString source;
    QTextStream ts(&source);

    ts << name << " " << objectName << ";";

    return source;
}


QString Component::getSourceForMain() const{
    if(type == DEFAULT || type == ARRAY || type == INTERVAL || type == STRINGSTREAM || type == SEQINFILE){
        return "";
    }

    QString source;
    QTextStream ts(&source);

    ts << objectName << ".addEnumerator(&" << enumeratorObjectName << ");" << Qt::endl;
    ts << objectName << ".run();" << Qt::endl;

    return source;
}

void Component::setEnumerator(int enumeratorID, QString enumeratorObjectName){
    if(this->enumeratorID == -1){
        this->enumeratorID = enumeratorID;
        this->enumeratorObjectName = enumeratorObjectName;
    }else if(this->enumeratorID == enumeratorID){
        this->enumeratorObjectName = enumeratorObjectName;
    }
}

QString Struct::getSource(){
    QString source;
    QTextStream ts(&source);

    ts << "struct " << name ;
    ts << Qt::endl << "{";

    foreach(Member member, members){
        ts << Qt::endl << "    " << member.type << " " <<  member.name << ";";
    }

    foreach(CustomMethod customMethod, customMethods){
        ts << Qt::endl << "    " << customMethod.header << Qt::endl << "    {";
        QTextStream methodBodyStream(&customMethod.body);
        while(!methodBodyStream.atEnd()){
            ts << Qt::endl << "        " << methodBodyStream.readLine();
        }
        ts << Qt::endl << "    " << "}";
    }

    ts << Qt::endl << "}";

    return source;
}
