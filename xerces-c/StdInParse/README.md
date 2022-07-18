 xerces-c: StdInParse
==============

This program demonstrates streaming XML data from standard input.  <br/>


Build and Run <br/>
% g++ StdInParse.cpp StdInParseHandlers.cpp   `pkg-config --cflags --libs xerces-c` -o parse  <br/>

% ./parse < personal.xml <br/>
> stdin: 6 ms (37 elems, 12 attrs, 134 spaces, 134 chars) <br/>


