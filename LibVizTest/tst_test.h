#ifndef TST_TEST_H
#define TST_TEST_H

#include <QtTest>

#include "../LibViz/model.h"

#define TEST

class Test : public QObject
{
    Q_OBJECT

public:
    Test();
    ~Test();

private:
    Model* model;
    Component* component;

private slots:
    void test_model_init();
    void test_new_id();
    void test_create_component_data();
    void test_create_component();
    void test_create_struct();
    void test_create_codeblock();
    void test_used_component_name();
    void test_used_object_name();
    void test_enumerator_name_by_id();
    void test_create_member();
    void test_create_method();
    void test_load_config();
    void test_setters();
    void test_compile_failed();
    void test_deletes();
    void test_signal_compiler_not_set();
    void test_signal_have_compile_output();
    void test_signal_compile_process_ended();
    void test_signal_need_project_name_for_save();
    void test_signal_need_project_name_for_open();
    void test_signal_want_to_generate_source();
    void test_signal_project_loaded();
};

#endif // TST_TEST_H
