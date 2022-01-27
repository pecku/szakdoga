#include "modelkit.h"

Component::Component(QString name, ComponentType type) : name(name), type(type){

}

QString Component::getSource(){
    QString source;
    QTextStream ts(&source);
    ts << Qt::endl << "class " << name << " : public " << componentTypeNameStrings[type] << "<" << "itemType" << ">";
    ts << Qt::endl << "{";
    ts << Qt::endl << "private:";
    foreach(Member member, members){
        ts << Qt::endl << member.type << " " <<  member.name << ";";
    }
    ts << Qt::endl << "public:";
    auto methodkeys = methods.keys();
    foreach(MethodType key, methodkeys){
        ts << Qt::endl << "\t" << methodHeaderStrings[key] << " override" << Qt::endl << "\t{";
        ts << Qt::endl << "\t" << methods[key];
        ts << Qt::endl << "\t" << "}";
    }
    ts << Qt::endl << "}";
    return source;
}
