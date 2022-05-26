#include "modelkit.h"

/*!
 * \brief Constructs a new Component object.
 * 
 * \param name The name of the component.
 * \param type The type of the component.
 * \param id The id of the component.
 */
Component::Component(QString name, ComponentType type, int id) : name(name), id(id), type(type){
    enumeratorID = -1;
    constructorParameter = "";
    if(type == DEFAULT || type == ARRAY || type == INTERVAL || type == STRINGSTREAM || type == SEQINFILE){
        useInMain = false;
    }else{
        useInMain = true;
    }
}

/*!
 * \brief Generates the source code of the component.
 * 
 * \return QString The generated source code.
 */
QString Component::getSource() const{
    QString source;
    QTextStream ts(&source);

    ts << "class " << name << " : public " << componentTypeNameStrings[type];

    ts << "<" << item;

    if(type == LINSEARCH){
        ts << "," << (optimist ? "true" : "false");
    }else if(type == MAXSEARCH){
        ts << "," << value;
        ts << "," << compare << "<" << value << ">";
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

    if(methods.contains(DESTRUCTOR)){
        ts << Qt::endl << "    ";
        ts << "~" << name;
        ts << methodHeaderStrings[DESTRUCTOR].first;
        ts << methodHeaderStrings[DESTRUCTOR].second << " override" << Qt::endl << "    {";
        QString methodBody = methods[DESTRUCTOR];
        QTextStream methodBodyStream(&methodBody);
        while(!methodBodyStream.atEnd()){
            ts << Qt::endl << "        " << methodBodyStream.readLine();
        }
        ts << Qt::endl << "    " << "}";
    }

    ts << Qt::endl << "protected:";

    auto methodkeys = methods.keys();
    foreach(MethodType key, methodkeys){
        if(key == DESTRUCTOR){
            continue;
        }

        ts << Qt::endl << "    ";

        if(key == NEUTRAL || key == ADD || key == FUNC){
            ts << value << " ";
        }else if(key == CURRENT){
            ts << item << " ";
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

/*!
 * \brief Generates the source code of the component that is used for object creation.
 * 
 * \return QString 
 */
QString Component::getSourceForObjectCreation() const{
    QString source;
    QTextStream ts(&source);

    ts << name << " " << objectName;
    if(constructorParameter != ""){
        ts << "(" << constructorParameter << ")";
    }
    ts << ";";

    return source;
}

/*!
 * \brief Generates the source code of the component that is used in the main function.
 * 
 * \return QString 
 */
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

/*!
 * \brief Sets the enumerator of the component.
 * 
 * \param enumeratorID The id of the enumerator.
 * \param enumeratorObjectName The object name of the enumerator.
 */
void Component::setEnumerator(int enumeratorID, QString enumeratorObjectName){
    this->enumeratorID = enumeratorID;
    this->enumeratorObjectName = enumeratorObjectName;
}

/*!
 * \brief Generates the source code of the Struct object.
 * 
 * \return QString The generated source code.
 */
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
