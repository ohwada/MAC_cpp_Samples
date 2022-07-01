QT hello1
===============

QT Sample <br/>
hello window <br/>

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/qt5/hello1/hello1.png" > <br/>

Build and Run <br/>
(1) qmake <br/>
(1-1) % qmake -project <br/>

(1-2) add the following to the end of hello1.pro <br/>

> QT+=widgets <br/>

(1-3) % qmake <br/>

(1-4) % make <br/>

(1-5) double click hello1.app <br/>

or
(1-6)% ./hello1.app/Contents/MacOS/hello1 <br/>

(2) g++ with pkgconfig <br/>

(2-1)% g++ hello.cpp -o hello -std=c++11 `pkg-config --cflags --libs Qt5Widgets`

(2-2) % ./hello <br/>


### Reference
- https://www.webcyou.com/?p=10581

