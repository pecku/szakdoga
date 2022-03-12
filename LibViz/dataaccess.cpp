#include "dataaccess.h"

DataAccess::DataAccess()
{

}

bool DataAccess::writeSource(QString source){
    QFile file("main.cpp");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);
    out << source;

    return true;
}
