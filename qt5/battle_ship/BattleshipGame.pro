#-------------------------------------------------
#
# Project created by QtCreator 2019-04-02T09:18:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BattleshipGame
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17

SOURCES += \
        src/main.cpp \
    src/saving/settings.cpp \
    src/saving/saving_manager.cpp \
    src/widgets/field_widget.cpp \
    src/models/square.cpp \
    src/models/ship.cpp \
    src/models/fleet.cpp \
    src/widgets/widget_painter.cpp \
    src/widgets/field_painter.cpp \
    src/models/battleship_game.cpp \
    src/main_window.cpp \
    src/models/battleship_game_ai.cpp

HEADERS += \
    src/saving/settings.h \
    src/saving/saving_manager.h \
    src/exceptions/game_exception.h \
    src/widgets/field_widget.h \
    src/models/square.h \
    src/models/ship.h \
    src/models/fleet.h \
    src/widgets/widget_painter.h \
    src/widgets/field_painter.h \
    src/models/battleship_game.h \
    src/main_window.h \
    src/models/battleship_game_ai.h \
    src/models/fire_result.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

DISTFILES += \
    other/settings.txt
