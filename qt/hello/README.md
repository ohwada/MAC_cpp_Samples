QT hello
===============

QT Sample <br/>
hello window <br/>

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/qt/hello/hello.png" > <br/>

Build and Run <br/>
(1) qmake <br/>
(1-1) % qmake -project <br/>

(1-2) add the following to the end of hello.pro <br/>

> QT+=widgets <br/>

(1-3) % qmake <br/>

(1-4) % make <br/>

(1-5)% ./hello.app/Contents/MacOS/hello <br/>

(2) g++ <br/>

(2-1) % g++ -c hello.cpp -std=c++17  -I/usr/local/lib/QtWidgets.framework/Headers -o hello.o <br/>

(2-2) % g++ hello.o -F/usr/local/lib -framework QtCore -framework QtWidgets  -framework QtGui -o hello <br/>

(2-3) % ./hello <br/>


### Reference
- https://www.webcyou.com/?p=10581

