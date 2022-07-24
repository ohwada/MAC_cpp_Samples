## change log
## 2022-06-01 K.OHWADA

CONFIG      += qscintilla2

# Comment this in to build a dynamic library supporting multiple architectures
# on macOS.
#QMAKE_APPLE_DEVICE_ARCHS = x86_64 arm64

HEADERS      = mainwindow.h
SOURCES      = main.cpp mainwindow.cpp
RESOURCES    = application.qrc

## 2022-06-01 : added the following

QT+=widgets

INCLUDEPATH = /usr/local/include

LIBS = -L/usr/local/lib -lqscintilla2_qt5
