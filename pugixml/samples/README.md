pugixml: samples
===============

samples in this directory, <br/>
downloaded from below <br/>
https://pugixml.org/docs/quickstart.html <br/>

### samples
- load_error_handling.cpp <br/>
This is an example of handling loading errors <br/>

- load_file.cpp <br/>
This is an example of loading XML document from file <br/>

- load_memory.cpp <br/>
This is an example of loading XML document from memory using one of these functions <br/>

- load_stream.cpp <br/>
This is a simple example of loading XML document from file using streams <br/>

- modify_add.cpp <br/>
This is an example of adding new attributes/nodes to the document <br/>

- modify_base.cpp <br/>
This is an example of setting node/attribute name and value <br/>

- modify_remove.cpp <br/>
This is an example of removing attributes/nodes from the document <br/>

- save_custom_writer.cpp <br/>
This is a simple example of custom writer for saving document data to STL string <br/>

- save_file.cpp <br/>
This is a simple example of saving XML document to file <br/>

- save_stream.cpp <br/>
This is a simple example of saving XML document to standard output <br/>

- traverse_base.cpp <br/>
pugixml provides several accessors that convert attribute value to some other type. <br/>

- traverse_iter.cpp <br/>
Here is an example of using iterators for document traversal

- traverse_rangefor.cpp <br/>
Here is an example of using C++11 range-based for loop for document traversal <br/>

- traverse_walker.cpp <br/>
This is an example of traversing tree hierarchy with xml_tree_walker <br/>

Build and Run <br/>
% g++  load_file.cpp `pkg-config --cflags --libs  pugixml` -o load <br/>
% ./load <br/>


