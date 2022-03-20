#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QProcess>
#include "modelkit.h"
#include "dataaccess.h"

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);

    QString generateSource();
    int createComponent(QString name, ComponentType type);
    int createCodeBlock();
    int createMember(int componentID);

    bool isComponentNameUsed(QString name);
    bool isObjectNameUsed(QString objectName);

    void modifyMember(int componentID, int memberID, QString type, QString name);

    void deleteComponent(int componentID);
    void deleteCodeBlock(int codeBlockID);
    void deleteMember(int componentID, int memberID);

    void setObjectName(int componentID, QString objectName);
    void setItem(int componentID, QString item){components[componentID]->setItem(item);}
    void setValue(int componentID, QString value){components[componentID]->setValue(value);}
    void setOptimist(int componentID, bool optimist){components[componentID]->setOptimist(optimist);}
    void setCompare(int componentID, QString compare){components[componentID]->setCompare(compare);}
    void setEnumerator(int componentID, int enumeratorID);
    void setMethod(int componentID, MethodType methodType, QString methodBody){components[componentID]->setMethod(methodType,methodBody);}

    void setCode(int codeBlockID, QString code){codeblocks[codeBlockID]->setCode(code);}

    void setCompilerPath(QString path);
    void setCompilerArguments(QString path);

    void setMainIdOrder(QVector<int> ids){mainIdOrder = ids;}

    void run();
    void compile();
    void stopCompile();

    QString getCompileOutput(){return compileOutput;}

private:
    QMap<int,Component*> components;
    QMap<int,CodeBlock*> codeblocks;
    QVector<int> mainIdOrder;
    int lastID;
    QString compilerPath;
    QStringList compilerArguments;
    bool compilerPathSet;
    QProcess* compileProcess;
    QString compileOutput;
    DataAccess dataAccess;

    int newID() {return ++lastID;}
    void loadConfig();
    QString generateMainSource();

signals:
    void compilerPathNotSet();
    void haveCompileOutput();
    void compileProcessEnded();

private slots:
    void compileFinished();
};

#endif // MODEL_H
