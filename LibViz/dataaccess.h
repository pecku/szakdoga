#ifndef DATAACCESS_H
#define DATAACCESS_H

#include <QString>
#include <QFile>
#include <QTextStream>

class DataAccess
{
public:
    DataAccess();

    bool writeSource(QString source);
};

#endif // DATAACCESS_H
