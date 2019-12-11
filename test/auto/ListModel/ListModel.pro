QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

HEADERS += \
    ListModelTest.h \
    ListModelTester.h \
    ListModelTester_p.h
SOURCES += \
    ListModelTest.cpp \
    ListModelTester.cpp

include(../../../src/QCxxListModel.pri)
