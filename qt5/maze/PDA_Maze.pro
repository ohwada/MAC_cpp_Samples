#-------------------------------------------------
#
# Project created by QtCreator 2014-02-26T04:03:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PDA_Maze
TEMPLATE = app

# Define App Version
DEFINES += APP_VERSION=\"0.1\"

SOURCES += main.cpp \
    CMainWindow.cpp \
    CIniConfig.cpp \
    CPlayField.cpp

HEADERS  += \
    CMainWindow.h \
    CIniConfig.h \
    CPlayField.h

OTHER_FILES += README.md \
    PDA_Maze.rc

RESOURCES += PDA_Maze.qrc

TRANSLATIONS += i18n/PDA_Maze_en.ts \
    i18n/PDA_Maze_ru.ts \
    i18n/PDA_Maze_es.ts

# Windows Executable Icon
win32:RC_FILE = PDA_Maze.rc
