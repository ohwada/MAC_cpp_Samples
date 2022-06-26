QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

INCLUDEPATH += $$PWD/../../src/models

DEPENDPATH += $$PWD/../../src/models

SOURCES += ../*.cpp\
           ../../src/models/*.cpp

HEADERS += ../*.h
