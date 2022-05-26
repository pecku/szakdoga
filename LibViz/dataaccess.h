#ifndef DATAACCESS_H
#define DATAACCESS_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>
#include <QTextStream>
#include "modelkit.h"

/*!
 * \brief Class representing a data access object. This class is used to read and write data from and to files.
 * 
 */
class DataAccess
{
public:
    DataAccess();

    bool writeSource(QString source);
    bool saveProject(SaveData data);
    SaveData loadProject(QString projectName);
};

#endif // DATAACCESS_H
