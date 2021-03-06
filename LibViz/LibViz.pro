QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    componentwidget.cpp \
    createcomponentdialog.cpp \
    custommethodwidget.cpp \
    dataaccess.cpp \
    enumeratorwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    memberwidget.cpp \
    model.cpp \
    modelkit.cpp \
    popuptextedit.cpp \
    procedurewidget.cpp \
    settingsdialog.cpp \
    structwidget.cpp \
    textinputdialog.cpp

HEADERS += \
    componentwidget.h \
    createcomponentdialog.h \
    custommethodwidget.h \
    dataaccess.h \
    enumeratorwidget.h \
    mainwindow.h \
    memberwidget.h \
    model.h \
    modelkit.h \
    popuptextedit.h \
    procedurewidget.h \
    settingsdialog.h \
    structwidget.h \
    textinputdialog.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
