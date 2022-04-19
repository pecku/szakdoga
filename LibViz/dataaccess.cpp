#include "dataaccess.h"

DataAccess::DataAccess()
{

}

bool DataAccess::writeSource(/*QString projectName,*/ QString source){
    QFile file("main.cpp");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);
    out << source;

    return true;
}

bool DataAccess::saveProject(SaveData data){
    QXmlStreamWriter xmlWriter;
    QFile file(data.projectName);
    if(!file.open(QIODevice::WriteOnly)){
        qDebug() << "Error opening file";
        return false;
    }
    QString mainIdOrder;
    QTextStream ts(&mainIdOrder);
    foreach(int id, data.mainIdOrder){
        ts<<id<<" ";
    }
    mainIdOrder = mainIdOrder.trimmed();
    xmlWriter.setDevice(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("project");
        xmlWriter.writeTextElement("name", data.projectName);
        xmlWriter.writeTextElement("mainIdOrder", mainIdOrder);
        xmlWriter.writeTextElement("lastID", QString::number(data.lastID));
        xmlWriter.writeStartElement("components");
            foreach(Component* component, data.components){
                xmlWriter.writeStartElement("component");
                    xmlWriter.writeTextElement("id", QString::number(component->getID()));
                    xmlWriter.writeTextElement("name", component->getName());
                    xmlWriter.writeTextElement("objectName", component->getObjectName());
                    xmlWriter.writeTextElement("type", componentTypeNameStrings[component->getType()]);
                    xmlWriter.writeTextElement("item", component->getItem());
                    xmlWriter.writeTextElement("enumeratorID", QString::number(component->getEnumeratorID()));
                    xmlWriter.writeTextElement("enumeratorObjectName", component->getEnumeratorObjectName());
                    xmlWriter.writeTextElement("optimist", component->getOptimist() ? "true" : "false");
                    xmlWriter.writeTextElement("value", component->getValue());
                    xmlWriter.writeTextElement("compare", component->getCompare());
                    xmlWriter.writeStartElement("members");
                        foreach(Member member, component->getMembers()){
                            xmlWriter.writeStartElement("member");
                                xmlWriter.writeTextElement("id", QString::number(member.id));
                                xmlWriter.writeTextElement("type", member.type);
                                xmlWriter.writeTextElement("name", member.name);
                            xmlWriter.writeEndElement();
                        }
                    xmlWriter.writeEndElement();
                    xmlWriter.writeStartElement("methods");
                        QMap<MethodType,QString> methods = component->getMethods();
                        foreach(const MethodType key, methods.keys()){
                            xmlWriter.writeStartElement("method");
                                xmlWriter.writeTextElement("type", methodTypeStrings[key]);
                                xmlWriter.writeTextElement("body", methods[key]);
                            xmlWriter.writeEndElement();
                        }
                    xmlWriter.writeEndElement();
                    xmlWriter.writeStartElement("custommethods");
                        foreach(CustomMethod customMethod, component->getCustomMethods()){
                            xmlWriter.writeStartElement("custommethod");
                                xmlWriter.writeTextElement("id", QString::number(customMethod.id));
                                xmlWriter.writeTextElement("header", customMethod.header);
                                xmlWriter.writeTextElement("body", customMethod.body);
                            xmlWriter.writeEndElement();
                        }
                    xmlWriter.writeEndElement();
                xmlWriter.writeEndElement();
            }
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("structs");
            foreach(Struct* _struct, data.structs){
                xmlWriter.writeStartElement("struct");
                    xmlWriter.writeTextElement("id", QString::number(_struct->getID()));
                    xmlWriter.writeTextElement("name", _struct->getName());
                    xmlWriter.writeStartElement("members");
                        foreach(Member member, _struct->getMembers()){
                            xmlWriter.writeStartElement("member");
                                xmlWriter.writeTextElement("id", QString::number(member.id));
                                xmlWriter.writeTextElement("type", member.type);
                                xmlWriter.writeTextElement("name", member.name);
                            xmlWriter.writeEndElement();
                        }
                    xmlWriter.writeEndElement();
                    xmlWriter.writeStartElement("custommethods");
                        foreach(CustomMethod customMethod, _struct->getCustomMethods()){
                            xmlWriter.writeStartElement("custommethod");
                                xmlWriter.writeTextElement("id", QString::number(customMethod.id));
                                xmlWriter.writeTextElement("header", customMethod.header);
                                xmlWriter.writeTextElement("body", customMethod.body);
                            xmlWriter.writeEndElement();
                        }
                    xmlWriter.writeEndElement();
                xmlWriter.writeEndElement();
            }
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("codeblocks");
            foreach(CodeBlock* codeblock, data.codeblocks){
                xmlWriter.writeStartElement("codeblock");
                    xmlWriter.writeTextElement("id", QString::number(codeblock->getID()));
                    xmlWriter.writeTextElement("code", codeblock->getCode());
                xmlWriter.writeEndElement();
            }
        xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();
    return true;
}

SaveData DataAccess::loadProject(QString projectName){
    QMap<int,Component*> components;
    QMap<int,CodeBlock*> codeblocks;
    QMap<int,Struct*> structs;
    QVector<int> mainIdOrder;
    int lastID = 0;

    QXmlStreamReader xmlReader;
    QFile file(projectName);
    file.open(QIODevice::ReadOnly);
    xmlReader.setDevice(&file);
    xmlReader.readNext();
    while(!xmlReader.atEnd()){
        if(xmlReader.isStartElement()){
            if(xmlReader.name().toString() == "project"){
                xmlReader.readNext();
                while(!xmlReader.atEnd()){
                    if(xmlReader.isStartElement()){
                        if(xmlReader.name().toString() == "mainIdOrder"){
                            xmlReader.readNext();
                            QString mainIdOrderString = xmlReader.text().toString();
                            QStringList mainIdOrderList = mainIdOrderString.split(" ");
                            foreach(QString id, mainIdOrderList){
                                mainIdOrder.push_back(id.toInt());
                            }
                        }
                        if(xmlReader.name().toString() == "lastID"){
                            xmlReader.readNext();
                            lastID = xmlReader.text().toInt();
                        }
                        if(xmlReader.name().toString() == "components"){
                            xmlReader.readNext();
                            while(!xmlReader.atEnd()){
                                if(xmlReader.isStartElement()){
                                    if(xmlReader.name().toString() == "component"){
                                        int id = 0;
                                        QString name = "";
                                        QString objectName = "";
                                        ComponentType type;
                                        QString item = "";
                                        int enumeratorID = 0;
                                        QString enumeratorObjectName = "";
                                        bool optimist = "";
                                        QString value = "";
                                        QString compare = "";
                                        QMap<MethodType,QString> methods;
                                        QMap<int,Member> members;
                                        QMap<int,CustomMethod> customMethods;
                                        xmlReader.readNext();
                                        while(!xmlReader.atEnd()){
                                            if(xmlReader.isStartElement()){
                                                if(xmlReader.name().toString() == "id"){
                                                    xmlReader.readNext();
                                                    id = xmlReader.text().toInt();
                                                }
                                                if(xmlReader.name().toString() == "name"){
                                                    xmlReader.readNext();
                                                    name = xmlReader.text().toString();
                                                }
                                                if(xmlReader.name().toString() == "objectName"){
                                                    xmlReader.readNext();
                                                    objectName = xmlReader.text().toString();
                                                }
                                                if(xmlReader.name().toString() == "type"){
                                                    xmlReader.readNext();
                                                    type = componentTypeFromString[xmlReader.text().toString()];
                                                }
                                                if(xmlReader.name().toString() == "item"){
                                                    xmlReader.readNext();
                                                    item = xmlReader.text().toString();
                                                }
                                                if(xmlReader.name().toString() == "enumeratorID"){
                                                    xmlReader.readNext();
                                                    enumeratorID = xmlReader.text().toInt();
                                                }
                                                if(xmlReader.name().toString() == "enumeratorObjectName"){
                                                    xmlReader.readNext();
                                                    enumeratorObjectName = xmlReader.text().toString();
                                                }
                                                if(xmlReader.name().toString() == "optimist"){
                                                    xmlReader.readNext();
                                                    optimist = xmlReader.text().toString() == "true" ? true : false;
                                                }
                                                if(xmlReader.name().toString() == "value"){
                                                    xmlReader.readNext();
                                                    value = xmlReader.text().toString();
                                                }
                                                if(xmlReader.name().toString() == "compare"){
                                                    xmlReader.readNext();
                                                    compare = xmlReader.text().toString();
                                                }
                                                if(xmlReader.name().toString() == "methods"){
                                                    xmlReader.readNext();
                                                    while(!xmlReader.atEnd()){
                                                        if(xmlReader.isStartElement()){
                                                            if(xmlReader.name().toString() == "method"){
                                                                QString type = "";
                                                                QString body = "";
                                                                xmlReader.readNext();
                                                                while(!xmlReader.atEnd()){
                                                                    if(xmlReader.isStartElement()){
                                                                        if(xmlReader.name().toString() == "type"){
                                                                            xmlReader.readNext();
                                                                            type = xmlReader.text().toString();
                                                                        }
                                                                        if(xmlReader.name().toString() == "body"){
                                                                            xmlReader.readNext();
                                                                            body = xmlReader.text().toString();
                                                                        }
                                                                    }
                                                                    if(xmlReader.isEndElement()){
                                                                        if(xmlReader.name().toString() == "method"){
                                                                            break;
                                                                        }
                                                                    }
                                                                    xmlReader.readNext();
                                                                }
                                                                if(!xmlReader.hasError()){
                                                                    methods.insert(methodTypeFromString[type], body);
                                                                }
                                                            }
                                                        }
                                                        if(xmlReader.isEndElement()){
                                                            if(xmlReader.name().toString() == "methods"){
                                                                break;
                                                            }
                                                        }
                                                        xmlReader.readNext();
                                                    }
                                                }
                                                if(xmlReader.name().toString() == "members"){
                                                    xmlReader.readNext();
                                                    while(!xmlReader.atEnd()){
                                                        if(xmlReader.isStartElement()){
                                                            if(xmlReader.name().toString() == "member"){
                                                                int id = 0;
                                                                QString type = "";
                                                                QString name = "";
                                                                xmlReader.readNext();
                                                                while(!xmlReader.atEnd()){
                                                                    if(xmlReader.isStartElement()){
                                                                        if(xmlReader.name().toString() == "id"){
                                                                            xmlReader.readNext();
                                                                            id = xmlReader.text().toInt();
                                                                        }
                                                                        if(xmlReader.name().toString() == "type"){
                                                                            xmlReader.readNext();
                                                                            type = xmlReader.text().toString();
                                                                        }
                                                                        if(xmlReader.name().toString() == "name"){
                                                                            xmlReader.readNext();
                                                                            name = xmlReader.text().toString();
                                                                        }
                                                                    }
                                                                    if(xmlReader.isEndElement()){
                                                                        if(xmlReader.name().toString() == "member"){
                                                                            break;
                                                                        }
                                                                    }
                                                                    xmlReader.readNext();
                                                                }
                                                                if(!xmlReader.hasError()){
                                                                    Member member = Member(id);
                                                                    member.type = type;
                                                                    member.name = name;
                                                                    members.insert(id,member);
                                                                }
                                                            }
                                                        }
                                                        if(xmlReader.isEndElement()){
                                                            if(xmlReader.name().toString() == "members"){
                                                                break;
                                                            }
                                                        }
                                                        xmlReader.readNext();
                                                    }
                                                }
                                                if(xmlReader.name().toString() == "custommethods"){
                                                    xmlReader.readNext();
                                                    while(!xmlReader.atEnd()){
                                                        if(xmlReader.isStartElement()){
                                                            if(xmlReader.name().toString() == "custommethod"){
                                                                int id = 0;
                                                                QString header = "";
                                                                QString body = "";
                                                                xmlReader.readNext();
                                                                while(!xmlReader.atEnd()){
                                                                    if(xmlReader.isStartElement()){
                                                                        if(xmlReader.name().toString() == "id"){
                                                                            xmlReader.readNext();
                                                                            id = xmlReader.text().toInt();
                                                                        }
                                                                        if(xmlReader.name().toString() == "header"){
                                                                            xmlReader.readNext();
                                                                            header = xmlReader.text().toString();
                                                                        }
                                                                        if(xmlReader.name().toString() == "body"){
                                                                            xmlReader.readNext();
                                                                            body = xmlReader.text().toString();
                                                                        }
                                                                    }
                                                                    if(xmlReader.isEndElement()){
                                                                        if(xmlReader.name().toString() == "custommethod"){
                                                                            break;
                                                                        }
                                                                    }
                                                                    xmlReader.readNext();
                                                                }
                                                                if(!xmlReader.hasError()){
                                                                    CustomMethod customMethod = CustomMethod(id);
                                                                    customMethod.header = header;
                                                                    customMethod.body = body;
                                                                    customMethods.insert(id,customMethod);
                                                                }
                                                            }
                                                        }
                                                        if(xmlReader.isEndElement()){
                                                            if(xmlReader.name().toString() == "custommethods"){
                                                                break;
                                                            }
                                                        }
                                                        xmlReader.readNext();
                                                    }
                                                }
                                            }
                                            if(xmlReader.isEndElement()){
                                                if(xmlReader.name().toString() == "component"){
                                                    break;
                                                }
                                            }
                                            xmlReader.readNext();
                                        }
                                        if(!xmlReader.hasError()){
                                            Component* component = new Component(name, type, id);
                                            component->setObjectName(objectName);
                                            component->setItem(item);
                                            component->setEnumerator(enumeratorID,enumeratorObjectName);
                                            component->setOptimist(optimist);
                                            component->setValue(value);
                                            component->setCompare(compare);
                                            component->setMethods(methods);
                                            component->setMembers(members);
                                            component->setCustomMethods(customMethods);
                                            components.insert(id,component);
                                        }
                                    }
                                }
                                if(xmlReader.isEndElement()){
                                    if(xmlReader.name().toString() == "components"){
                                        break;
                                    }
                                }
                                xmlReader.readNext();
                            }
                        }
                        if(xmlReader.name().toString() == "structs"){
                            xmlReader.readNext();
                            while(!xmlReader.atEnd()){
                                if(xmlReader.isStartElement()){
                                    if(xmlReader.name().toString() == "struct"){
                                        int id = 0;
                                        QString name = "";
                                        QMap<int,Member> members;
                                        QMap<int,CustomMethod> customMethods;
                                        xmlReader.readNext();
                                        while(!xmlReader.atEnd()){
                                            if(xmlReader.isStartElement()){
                                                if(xmlReader.name().toString() == "id"){
                                                    xmlReader.readNext();
                                                    id = xmlReader.text().toInt();
                                                }
                                                if(xmlReader.name().toString() == "name"){
                                                    xmlReader.readNext();
                                                    name = xmlReader.text().toString();
                                                }
                                                if(xmlReader.name().toString() == "members"){
                                                    xmlReader.readNext();
                                                    while(!xmlReader.atEnd()){
                                                        if(xmlReader.isStartElement()){
                                                            if(xmlReader.name().toString() == "member"){
                                                                int id = 0;
                                                                QString type = "";
                                                                QString name = "";
                                                                xmlReader.readNext();
                                                                while(!xmlReader.atEnd()){
                                                                    if(xmlReader.isStartElement()){
                                                                        if(xmlReader.name().toString() == "id"){
                                                                            xmlReader.readNext();
                                                                            id = xmlReader.text().toInt();
                                                                        }
                                                                        if(xmlReader.name().toString() == "type"){
                                                                            xmlReader.readNext();
                                                                            type = xmlReader.text().toString();
                                                                        }
                                                                        if(xmlReader.name().toString() == "name"){
                                                                            xmlReader.readNext();
                                                                            name = xmlReader.text().toString();
                                                                        }
                                                                    }
                                                                    if(xmlReader.isEndElement()){
                                                                        if(xmlReader.name().toString() == "member"){
                                                                            break;
                                                                        }
                                                                    }
                                                                    xmlReader.readNext();
                                                                }
                                                                if(!xmlReader.hasError()){
                                                                    Member member = Member(id);
                                                                    member.type = type;
                                                                    member.name = name;
                                                                    members.insert(id,member);
                                                                }
                                                            }
                                                        }
                                                        if(xmlReader.isEndElement()){
                                                            if(xmlReader.name().toString() == "members"){
                                                                break;
                                                            }
                                                        }
                                                        xmlReader.readNext();
                                                    }
                                                }
                                                if(xmlReader.name().toString() == "custommethods"){
                                                    xmlReader.readNext();
                                                    while(!xmlReader.atEnd()){
                                                        if(xmlReader.isStartElement()){
                                                            if(xmlReader.name().toString() == "custommethod"){
                                                                int id = 0;
                                                                QString header = "";
                                                                QString body = "";
                                                                xmlReader.readNext();
                                                                while(!xmlReader.atEnd()){
                                                                    if(xmlReader.isStartElement()){
                                                                        if(xmlReader.name().toString() == "id"){
                                                                            xmlReader.readNext();
                                                                            id = xmlReader.text().toInt();
                                                                        }
                                                                        if(xmlReader.name().toString() == "header"){
                                                                            xmlReader.readNext();
                                                                            header = xmlReader.text().toString();
                                                                        }
                                                                        if(xmlReader.name().toString() == "body"){
                                                                            xmlReader.readNext();
                                                                            body = xmlReader.text().toString();
                                                                        }
                                                                    }
                                                                    if(xmlReader.isEndElement()){
                                                                        if(xmlReader.name().toString() == "custommethod"){
                                                                            break;
                                                                        }
                                                                    }
                                                                    xmlReader.readNext();
                                                                }
                                                                if(!xmlReader.hasError()){
                                                                    CustomMethod customMethod = CustomMethod(id);
                                                                    customMethod.header = header;
                                                                    customMethod.body = body;
                                                                    customMethods.insert(id,customMethod);
                                                                }
                                                            }
                                                        }
                                                        if(xmlReader.isEndElement()){
                                                            if(xmlReader.name().toString() == "custommethods"){
                                                                break;
                                                            }
                                                        }
                                                        xmlReader.readNext();
                                                    }
                                                }
                                            }
                                            if(xmlReader.isEndElement()){
                                                if(xmlReader.name().toString() == "struct"){
                                                    break;
                                                }
                                            }
                                            xmlReader.readNext();
                                        }
                                        if(!xmlReader.hasError()){
                                            Struct* _struct = new Struct(name,id);
                                            _struct->setMembers(members);
                                            _struct->setCustomMethods(customMethods);
                                            structs.insert(id,_struct);
                                        }
                                    }
                                }
                                if(xmlReader.isEndElement()){
                                    if(xmlReader.name().toString() == "structs"){
                                        break;
                                    }
                                }
                                xmlReader.readNext();
                            }
                        }
                        if(xmlReader.name().toString() == "codeblocks"){
                            xmlReader.readNext();
                            while(!xmlReader.atEnd()){
                                if(xmlReader.isStartElement()){
                                    if(xmlReader.name().toString() == "codeblock"){
                                        int id = 0;
                                        QString code = "";
                                        xmlReader.readNext();
                                        while(!xmlReader.atEnd()){
                                            if(xmlReader.isStartElement()){
                                                if(xmlReader.name().toString() == "id"){
                                                    xmlReader.readNext();
                                                    id = xmlReader.text().toInt();
                                                }
                                                if(xmlReader.name().toString() == "code"){
                                                    xmlReader.readNext();
                                                    code = xmlReader.text().toString();
                                                }
                                            }
                                            if(xmlReader.isEndElement()){
                                                if(xmlReader.name().toString() == "codeblock"){
                                                    break;
                                                }
                                            }
                                            xmlReader.readNext();
                                        }
                                        if(!xmlReader.hasError()){
                                            CodeBlock* cb = new CodeBlock(id);
                                            cb->setCode(code);
                                            codeblocks.insert(id,cb);
                                        }
                                    }
                                }
                                if(xmlReader.isEndElement()){
                                    if(xmlReader.name().toString() == "codeblocks"){
                                        break;
                                    }
                                }
                                xmlReader.readNext();
                            }
                        }
                    }
                    if(xmlReader.isEndElement()){
                        if(xmlReader.name().toString() == "project"){
                            break;
                        }
                    }
                    xmlReader.readNext();
                }
            }
        }
        xmlReader.readNext();
    }
    file.close();

    SaveData loadData(projectName,components,codeblocks,structs,mainIdOrder,lastID);
    return loadData;
}
