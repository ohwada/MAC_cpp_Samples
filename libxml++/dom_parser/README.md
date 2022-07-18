libxml++: dom parser
===============

DOM Parser <br/>
This example looks in the document for expected elements and then examines them. All these examples are included in the libxml++ source distribution. <br/>

Build and Run <br/>
% g++  main.cc -std=c++11 `pkg-config --cflags --libs libxml++-2.6` -o dom <br/>

% ./dom <br/>
> Node name = example <br/>
>     line = 4 <br/>

