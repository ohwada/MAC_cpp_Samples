libxml++: sax parser
===============

SAX Parser <br/>
This example shows how the handler methods are called during parsing. <br/>

Build and Run <br/>
% g++  main.cc myparser.cc -std=c++11 `pkg-config --cflags --libs libxml++-2.6` -o sax <br/>

% ./sax <br/>
> on_start_document() <br/>
> node name=gjob:Helping <br/>
> Attribute name=xmlns:gjob, <br/>
> value= https://libxmlplusplus.github.io/libxmlplusplus <br/> on_characters(): <br/>

