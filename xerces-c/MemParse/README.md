 xerces-c: MemParse
==============

This sample program illustrates how one can use a memory buffer as the input to parser. <br/>


Build and Run <br/>
% g++ MemParse.cpp MemParseHandlers.cpp  `pkg-config --cflags --libs xerces-c` -o parse<br/>

% ./parse <br/>
> Parsing took 0 ms (4 elements, 1 attributes, 16 spaces, 95 characters). <br/>

