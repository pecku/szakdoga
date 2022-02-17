#include "modelkit.h"

Component::Component(QString name, ComponentType type) : name(name), type(type){

}

QString Component::getSource(){
    QString source;
    QTextStream ts(&source);
    ts << "class " << name << " : public " << componentTypeNameStrings[type] << "<" << item << ">";
    ts << Qt::endl << "{";
    ts << Qt::endl << "private:";
    foreach(Member member, members){
        ts << Qt::endl << "\t" << member.type << " " <<  member.name << ";";
    }
    ts << Qt::endl << "public:";
    auto methodkeys = methods.keys();
    foreach(MethodType key, methodkeys){
        ts << Qt::endl << "\t" << methodHeaderStrings[key] << " override" << Qt::endl << "\t{";
        QTextStream methodBodyStream(&methods[key]);
        while(!methodBodyStream.atEnd()){
            ts << Qt::endl << "\t\t" << methodBodyStream.readLine();
        }
        ts << Qt::endl << "\t" << "}";
    }
    ts << Qt::endl << "}";

    return source;
}


/*
QString format =
"class %s : public %s<%s>{\n\
protected:\n\
    %s %s;\n\
    %s %s;\n\
}\
";
return QString::asprintf(format.toStdString().c_str(),name.toStdString().c_str(),componentTypeNameStrings[type].toStdString().c_str(),item.toStdString().c_str(),"asd","asd1","asd2","asd3");
*/
