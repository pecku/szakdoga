#include "tst_test.h"

Test::Test()
{
    model = new Model();
    component = new Component("TestComponent",SUMMATION,0);
}

Test::~Test()
{

}

/*!
 * \brief Test for model creation. Checks if the created model has the correct initial values.
 * 
 */
void Test::test_model_init(){
    QCOMPARE(model->projectName, "");
    QCOMPARE(model->components.size(), 0);
    QCOMPARE(model->codeblocks.size(), 0);
    QCOMPARE(model->structs.size(), 0);
    QCOMPARE(model->mainIdOrder.size(), 0);
    QCOMPARE(model->lastID, 0);
    QVERIFY(!model->compileFailed);
}

/*!
 * \brief Test for id creation. Checks if the the created id is appropriate and the variable storing the last id changes as expected.
 * 
 */
void Test::test_new_id(){
    int lastId = model->lastID;
    QCOMPARE(model->newID(), lastId+1);
    QCOMPARE(model->lastID, lastId+1);
}

/*!
 * \brief Data for test_create_component test case.
 * 
 */
void Test::test_create_component_data(){
    QTest::addColumn<QString>("component_name");
    QTest::addColumn<ComponentType>("component_type");

    QTest::newRow("counting") << "CountingComponent" << COUNTING;
    QTest::newRow("linsearch") << "LinSearchComponent" << LINSEARCH;
    QTest::newRow("maxsearch") << "MaxSearchComponent" << MAXSEARCH;
    QTest::newRow("selection") << "SelectionComponent" << SELECTION;
    QTest::newRow("summation") << "SummationComponent" << SUMMATION;
    QTest::newRow("default") << "DefaultEnorComponent" << DEFAULT;
    QTest::newRow("array") << "ArrayComponent" << ARRAY;
    QTest::newRow("interval") << "IntervalComponent" << INTERVAL;
    QTest::newRow("stringstream") << "StringStreamComponent" << STRINGSTREAM;
    QTest::newRow("seqinfile") << "SeqInFileComponent" << SEQINFILE;
}

/*!
 * \brief Test for component creation. Checks if the created component has the correct initial values.
 * 
 */
void Test::test_create_component()
{
    QFETCH(QString, component_name);
    QFETCH(ComponentType, component_type);

    model->createComponent(component_name, component_type);
    Component* component = model->components[model->lastID];
    QCOMPARE(component->getName(), component_name);
    QCOMPARE(component->getType(), component_type);
    QCOMPARE(component->getID(), model->lastID);
}

/*!
 * \brief Test for struct creation. Checks if the created struct has the correct initial values.
 * 
 */
void Test::test_create_struct()
{
    QString name = "TestStruct";
    model->createStruct(name);
    Struct* _struct = model->structs[model->lastID];
    QCOMPARE(_struct->getName(), name);
    QCOMPARE(_struct->getID(), model->lastID);
}

/*!
 * \brief Test for codeblock creation. Checks if the created codeblock has the correct initial values.
 * 
 */
void Test::test_create_codeblock(){
    model->createCodeBlock();
    CodeBlock* codeblock = model->codeblocks[model->lastID];
    QCOMPARE(codeblock->getCode(), "");
    QCOMPARE(codeblock->getID(), model->lastID);
}

/*!
 * \brief Test for used component names. Checks if the given component name's status is recognized as expected (used or not).
 * 
 */
void Test::test_used_component_name(){
    QVERIFY(model->isComponentNameUsed("CountingComponent"));
    QVERIFY(model->isComponentNameUsed("TestStruct"));
    QVERIFY(!model->isComponentNameUsed("notInUseComponentName"));
}

/*!
 * \brief Test for used object names. Checks if the given object name's status is recognized as expected (used or not).
 * 
 */
void Test::test_used_object_name(){
    model->setObjectName(2, "usedObjectName");
    QVERIFY(model->isObjectNameUsed("usedObjectName"));
    QVERIFY(!model->isObjectNameUsed("notInUseObjectName"));
}

/*!
 * \brief Test for getting an enumerator's name from its id. Checks if the returned name is correct.
 * 
 */
void Test::test_enumerator_name_by_id(){
    QCOMPARE(model->getEnumeratorNameById(9), "IntervalComponent");
}

/*!
 * \brief Test for member creation. Checks if a member is created in the correct component object.
 * 
 */
void Test::test_create_member(){
    model->components[0] = component;
    QCOMPARE(component->getMembers().size(), 0);
    model->createMember(0);
    QCOMPARE(component->getMembers().size(), 1);
}

/*!
 * \brief Test for method creation. Checks if a method is created in the correct component object.
 * 
 */
void Test::test_create_method(){
    model->components[0] = component;
    QCOMPARE(component->getCustomMethods().size(), 0);
    model->createCustomMethod(0);
    QCOMPARE(component->getCustomMethods().size(), 1);
}

/*!
 * \brief Test for saved settings load. Checks the model can load the previously saved settings correctly.
 * 
 */
void Test::test_load_config(){
    QString path = "This/Is/A/Path";
    model->settings->setValue("CompilerPath",path);
    QStringList compilerArguments = QString("arg1 arg2 arg3").split(" ");
    model->settings->setValue("CompilerArguments",compilerArguments);

    model->loadConfig();
    compilerArguments.prepend("main.cpp");

    QCOMPARE(model->compilerPath, path);
    QCOMPARE(model->compilerArguments, compilerArguments);
    QVERIFY(model->compilerPathSet);
}

/*!
 * \brief Test for model setter methods. Checks if after setting the model's properties, the correct values are set.
 * 
 */
void Test::test_setters(){
    model->components[0] = component;
    component->createMember(20000);
    model->modifyMember(0, 20000, "setterTestMemmberType", "setterTestMemberName");
    component->createCustomMethod(20001);
    model->modifyCustomMethod(0, 20001, "setterTestMethodHeader", "setterTestMethodBody");
    model->setUseInMain(0, false);
    model->setObjectName(0, "setterTestObjectName");
    model->setItem(0, "setterTestItem");
    model->setValue(0, "setterTestValue");
    model->setOptimist(0, true);
    model->setCompare(0, "Greater");
    Component* enor = new Component("SetterTestEnor", DEFAULT, 25000);
    enor->setObjectName("SetterTestEnorObjectName");
    model->components[25000] = enor;
    model->setEnumerator(0, 25000);
    model->setMethod(0, DESTRUCTOR, "setterTestDestructorBody");
    model->setConstructorParameter(0, "setterTestConstructorParameter");
    CodeBlock* codeblock = new CodeBlock(30000);
    model->codeblocks[30000] = codeblock;
    model->setCode(30000, "setterTestCode");

    auto members = component->getMembers();
    auto custommethods = component->getCustomMethods();
    auto methods = component->getMethods();
    QCOMPARE(members[20000].type, "setterTestMemmberType");
    QCOMPARE(members[20000].name, "setterTestMemberName");
    QCOMPARE(custommethods[20001].header, "setterTestMethodHeader");
    QCOMPARE(custommethods[20001].body, "setterTestMethodBody");
    QVERIFY(!component->getUseInMain());
    QCOMPARE(component->getObjectName(), "setterTestObjectName");
    QCOMPARE(component->getItem(), "setterTestItem");
    QCOMPARE(component->getValue(), "setterTestValue");
    QVERIFY(component->getOptimist());
    QCOMPARE(component->getEnumeratorID(), 25000);
    QCOMPARE(methods[DESTRUCTOR], "setterTestDestructorBody");
    QCOMPARE(component->getConstructorParameter(), "setterTestConstructorParameter");
    QCOMPARE(codeblock->getCode(), "setterTestCode");
}

/*!
 * \brief Test for compilation errors. Checks if the model can detect compilation errors correctly.
 * 
 */
void Test::test_compile_failed(){
    model->compileFailed = false;
    model->compileFinished(1,QProcess::ExitStatus::CrashExit);
    QVERIFY(model->compileFailed);
    model->compileFailed = false;
    model->compileError(QProcess::ProcessError::Crashed);
    QVERIFY(model->compileFailed);
}

/*!
 * \brief Test for deletions. Checks if the model can delete the correct objects from the correct places.
 * 
 */
void Test::test_deletes(){
    auto members = component->getMembers();
    QVERIFY(members.contains(20000));
    model->deleteMember(0, 20000);
    members = component->getMembers();
    QVERIFY(!members.contains(20000));
    auto custommethods = component->getCustomMethods();
    QVERIFY(custommethods.contains(20001));
    model->deleteCustomMethod(0, 20001);
    custommethods = component->getCustomMethods();
    QVERIFY(!custommethods.contains(20001));
    QVERIFY(model->components.contains(0));
    model->deleteComponent(0);
    QVERIFY(!model->components.contains(0));
    QVERIFY(model->codeblocks.contains(30000));
    model->deleteCodeBlock(30000);
    QVERIFY(!model->codeblocks.contains(30000));
    model->structs[35000] = new Struct("DeleteTestStruct", 35000);
    QVERIFY(model->structs.contains(35000));
    model->deleteStruct(35000);
    QVERIFY(!model->structs.contains(35000));
}

/*!
 * \brief Test for the 'compiler not set' signal. Checks if the correct signal is emitted at the correct time.
 * 
 */
void Test::test_signal_compiler_not_set(){
    model->compilerPathSet = false;
    QSignalSpy spy(model, SIGNAL(compilerPathNotSet()));
    model->compile();
    QCOMPARE(spy.count(), 1);
}

/*!
 * \brief Test for the 'have compile output' signal. Checks if the correct signal is emitted at the correct time.
 * 
 */
void Test::test_signal_have_compile_output(){
    QSignalSpy spy(model, SIGNAL(haveCompileOutput(QString)));
    model->compileFinished(0,QProcess::ExitStatus::NormalExit);
    model->compileError(QProcess::ProcessError::Crashed);
    QCOMPARE(spy.count(), 2);
    QList<QVariant> arguments = spy.takeFirst();
    arguments.at(0).typeId();
    QVERIFY(arguments.at(0).typeId() == QMetaType::QString);
}

/*!
 * \brief Test for the 'compile process ended' signal. Checks if the correct signal is emitted at the correct time.
 * 
 */
void Test::test_signal_compile_process_ended(){
    QSignalSpy spy(model, SIGNAL(compileProcessEnded()));
    model->compileFinished(0,QProcess::ExitStatus::NormalExit);
    model->compileError(QProcess::ProcessError::Crashed);
    QCOMPARE(spy.count(), 2);
}

/*!
 * \brief Test for the 'need project name for save' signal. Checks if the correct signal is emitted at the correct time.
 * 
 */
void Test::test_signal_need_project_name_for_save(){
    QSignalSpy spy(model, SIGNAL(needProjectNameForSave()));
    model->saveProject();
    model->newProject();
    QCOMPARE(spy.count(), 2);
}

/*!
 * \brief Test for the 'need project name for open' signal. Checks if the correct signal is emitted at the correct time.
 * 
 */
void Test::test_signal_need_project_name_for_open(){
    QSignalSpy spy(model, SIGNAL(needProjectNameForOpen()));
    model->openProject();
    QCOMPARE(spy.count(), 1);
}

/*!
 * \brief Test for the 'want to generate source' signal. Checks if the correct signal is emitted at the correct time.
 * 
 */
void Test::test_signal_want_to_generate_source(){
    QSignalSpy spy(model, SIGNAL(wantToGenerateSource()));
    model->compilerPathSet = true;
    model->compile();
    QCOMPARE(spy.count(), 1);
}

/*!
 * \brief Test for the 'project loaded' signal. Checks if the correct signal is emitted at the correct time.
 * 
 */
void Test::test_signal_project_loaded(){
    QSignalSpy spy(model, SIGNAL(projectLoaded(SaveData)));
    model->projectName = "project";
    model->openProject();
    QCOMPARE(spy.count(), 1);
}

QTEST_APPLESS_MAIN(Test)
