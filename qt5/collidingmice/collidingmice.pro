# collidingmice.pro
# https://stuff.mit.edu/afs/athena/software/texmaker_v5.0.2/qt57/doc/qtwidgets/qtwidgets-graphicsview-collidingmice-collidingmice-pro.html

  QT += widgets

  HEADERS += \
          mouse.h
  SOURCES += \
          main.cpp \
          mouse.cpp

  RESOURCES += \
          mice.qrc

  # install
  target.path = $$[QT_INSTALL_EXAMPLES]/widgets/graphicsview/collidingmice
  INSTALLS += target

