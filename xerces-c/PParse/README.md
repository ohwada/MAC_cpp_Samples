 xerces-c: PParse
==============

This sample program demonstrates the progressive parse capabilities of the parser system. <br/>

Build and Run <br/>
% g++ PParse.cpp PParseHandlers.cpp `pkg-config --cflags --libs xerces-c` -o parse <br/>

% ./parse ../data/personal.xml <br/>
> ../data/personal.xml: 1 ms (37 elems, 12 attrs, 134 spaces, 134 chars) <br/>

