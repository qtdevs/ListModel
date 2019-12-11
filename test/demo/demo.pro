QT += quick

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

HEADERS += \
    DemoCore.h \
    DemoCore_p.h \
    DemoNode.h \
    DemoNode_p.h
SOURCES += \
    DemoCore.cpp \
    DemoNode.cpp

SOURCES += \
        main.cpp

RESOURCES += qml.qrc

include(../../src/QCxxListModel.pri)
