qt5 setup
===============

### install

% brew install qt <br/>
https://formulae.brew.sh/formula/qt <br/>

### setup
 link qmake and pkgconfig flies to system area <br/>
% bash setup.sh <br/>
https://github.com/ohwada/MAC_cpp_Samples/blob/master/qt5/setup/setup.sh <br/>

check <br/>
% qmake -v <br/>
> QMake version 3.1 <br/>
> Using Qt version 5.15.3 in /usr/local/Cellar/qt@5/5.15.3/lib <br/>

% pkg-config --cflags --libs Qt5Widgets <br/>
> -DQT_WIDGETS_LIB -F/usr/local/Cellar/qt@5/5.15.3/lib <br/>
> -DQT_GUI_LIB -F/usr/local/Cellar/qt@5/5.15.3/lib <br/>
> -DQT_CORE_LIB -F/usr/local/Cellar/qt@5/5.15.3/lib <br/>
> -I/usr/local/Cellar/qt@5/5.15.3/lib/QtWidgets.framework/Headers <br/>
> -I/usr/local/Cellar/qt@5/5.15.3/lib/QtGui.framework/Headers <br/>
> -I/usr/local/Cellar/qt@5/5.15.3/lib/QtCore.framework/Headers <br/>
> -F/usr/local/Cellar/qt@5/5.15.3/lib -framework QtWidgets <br/>
> -F/usr/local/Cellar/qt@5/5.15.3/lib -framework QtGui <br/>
> -F/usr/local/Cellar/qt@5/5.15.3/lib -framework QtCore <br/>

