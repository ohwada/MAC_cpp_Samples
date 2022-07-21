 xalan-c: sample
==============

 ### sample
- tansform.cpp <br/>
// transform file sample.xml according to the conversion rules written in file sample.xsl <br/>

Build and Run: <br/>
Require: <br/>
- xalan-c <br/>
- xerces-c <br/>

% g++ tansform.cpp -o transform `pkg-config --cflags --libs xalan-c` `pkg-config --cflags --libs xerces-c` <br/>
% ./transform > out.xml <br/>


