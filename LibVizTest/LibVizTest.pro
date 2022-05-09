QT += testlib
QT += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_test.cpp \
    ../LibViz/componentwidget.cpp \
    ../LibViz/createcomponentdialog.cpp \
    ../LibViz/custommethodwidget.cpp \
    ../LibViz/dataaccess.cpp \
    ../LibViz/enumeratorwidget.cpp \
    ../LibViz/main.cpp \
    ../LibViz/mainwindow.cpp \
    ../LibViz/memberwidget.cpp \
    ../LibViz/model.cpp \
    ../LibViz/modelkit.cpp \
    ../LibViz/popuptextedit.cpp \
    ../LibViz/procedurewidget.cpp \
    ../LibViz/settingsdialog.cpp \
    ../LibViz/structwidget.cpp \
    ../LibViz/textinputdialog.cpp

SUBDIRS += \
    ../LibViz/LibViz.pro

RESOURCES += \
    ../LibViz/resources.qrc

DISTFILES += \
    ../LibViz/icons/build_button.svg \
    ../LibViz/icons/delete_button.svg \
    ../LibViz/icons/generate_button.svg \
    ../LibViz/icons/load_project_button.svg \
    ../LibViz/icons/new_button.svg \
    ../LibViz/icons/new_project_button.svg \
    ../LibViz/icons/plus_button.svg \
    ../LibViz/icons/run_button.svg \
    ../LibViz/icons/save_project_button.svg \
    ../LibViz/icons/settings_button.svg \
    ../LibViz/icons/stop_button.svg

HEADERS += \
    ../LibViz/componentwidget.h \
    ../LibViz/createcomponentdialog.h \
    ../LibViz/custommethodwidget.h \
    ../LibViz/dataaccess.h \
    ../LibViz/enumeratorwidget.h \
    ../LibViz/library/library.hpp \
    ../LibViz/mainwindow.h \
    ../LibViz/memberwidget.h \
    ../LibViz/model.h \
    ../LibViz/modelkit.h \
    ../LibViz/popuptextedit.h \
    ../LibViz/procedurewidget.h \
    ../LibViz/settingsdialog.h \
    ../LibViz/structwidget.h \
    ../LibViz/textinputdialog.h \
    tst_test.h
