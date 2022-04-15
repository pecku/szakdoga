#ifndef DATAACCESS_H
#define DATAACCESS_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>
#include <QTextStream>
#include <modelkit.h>

class DataAccess
{
public:
    DataAccess();

    bool writeSource(/*QString projectName,*/ QString source);
    bool saveProject(SaveData data);
    SaveData loadProject(QString projectName);
};

#endif // DATAACCESS_H
