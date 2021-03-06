#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QProcess>
#include <QSettings>
#include "modelkit.h"
#include "dataaccess.h"

/*!
 * \brief The class representing the model that is the brain behind the whole application.
 * 
 */
class Model : public QObject
{
    Q_OBJECT

    friend class Test;

public:
    explicit Model(QObject *parent = nullptr);

    QString generateSource();
    int createComponent(QString name, ComponentType type);
    int createCodeBlock();
    int createStruct(QString name);
    int createMember(int componentID);
    int createCustomMethod(int componentID);

    bool isComponentNameUsed(QString name);
    bool isObjectNameUsed(QString objectName);
    QString getEnumeratorNameById(int enumeratorID);

    void modifyMember(int componentID, int memberID, QString type, QString name);
    void modifyCustomMethod(int componentID, int customMethodID, QString header, QString body);

    void deleteComponent(int componentID);
    void deleteCodeBlock(int codeBlockID);
    void deleteStruct(int structID);
    void deleteMember(int componentID, int memberID);
    void deleteCustomMethod(int componentID, int customMethodID);

    void setUseInMain(int componentID, bool useInMain){components[componentID]->setUseInMain(useInMain);}
    void setObjectName(int componentID, QString objectName);
    void setItem(int componentID, QString item){components[componentID]->setItem(item);}
    void setValue(int componentID, QString value){components[componentID]->setValue(value);}
    void setOptimist(int componentID, bool optimist){components[componentID]->setOptimist(optimist);}
    void setCompare(int componentID, QString compare){components[componentID]->setCompare(compare);}
    void setEnumerator(int componentID, int enumeratorID);
    void setMethod(int componentID, MethodType methodType, QString methodBody);
    void setConstructorParameter(int componentID, QString constructorParameter){components[componentID]->setConstructorParameter(constructorParameter);}

    void setCode(int codeBlockID, QString code){codeblocks[codeBlockID]->setCode(code);}

    void setCompilerPath(QString path);
    void setCompilerArguments(QString path);

    void setMainIdOrder(QVector<int> ids){mainIdOrder = ids;}

    void run();
    void compile();
    void stopCompile();

    QString getCompileOutput(){return compileOutput;}
    QString getCompilerPath(){return compilerPath;}
    QStringList getCompilerArguments(){return compilerArguments;}

    QString getProjectName(){return projectName;}

    bool newProject();
    bool saveProject();
    void setProject(QString file){projectName = file;}
    void openProject();

private:
    QString projectName;
    QMap<int,Component*> components;
    QMap<int,CodeBlock*> codeblocks;
    QMap<int,Struct*> structs;
    QVector<int> mainIdOrder;
    int lastID;
    QString compilerPath;
    QStringList compilerArguments;
    bool compilerPathSet;
    QProcess* compileProcess;
    QString compileOutput;
    bool compileFailed;
    DataAccess dataAccess;
    QSettings* settings;

    int newID() {return ++lastID;}
    void loadConfig();
    QString generateMainSource();

    QString replaceReference(QString codeString);
    QString getReferenceSource(QString objectName);

signals:
    void compilerPathNotSet();
    void haveCompileOutput(QString output);
    void compileProcessEnded();
    void needProjectNameForSave();
    void needProjectNameForOpen();
    void wantToGenerateSource();
    void projectLoaded(const SaveData& data);
    void cleared();

private slots:
    void compileFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void compileError(QProcess::ProcessError error);
};

#endif // MODEL_H
