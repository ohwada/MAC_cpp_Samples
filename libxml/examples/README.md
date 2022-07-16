libxml: exsamples
===============

libxml examples <br/>

examples in this directory, <br/>
downloaded from below <br/>
 http://www.xmlsoft.org/examples/ <br/>


### examples
- parse1.c  <br/>
Parse an XML file to a tree and free it  <br/>

- parse2.c  <br/>
Parse and validate an XML file to a tree and free the result  <br/>

- parse3.c  <br/>
Parse an XML document in memory to a tree and free it  <br/>

- parse4.c  <br/>
Parse an XML document chunk by chunk to a tree and free it  <br/>

- reader1.c  <br/>
 Parse an XML file with an xmlReader  <br/>

- reader2.c  <br/>
Parse and validate an XML file with an xmlReader  <br/>

- reader3.c  <br/>
Show how to extract subdocuments with xmlReader  <br/>

- reader4.c  <br/>
Parse multiple XML files reusing an xmlReader  <br/>

- tree1.c  <br/>
Navigates a tree to print element names  <br/>

- tree2.c  <br/>
Creates a tree  <br/>

- xpath1.c  <br/>
Evaluate XPath expression and prints result node set.  <br/>

- xpath2.c  <br/>
Load a document, locate subelements with XPath, modify said elements and save the resulting document.  <br/>

- io1.c  <br/>
Example of custom Input/Output  <br/>

- io2.c  <br/>
Output to char buffer  <br/>

- testWriter.c 
use various APIs for the xmlWriter  <br/>

Build and Run <br/>
% gcc  parse1.c -o parse1 `xml2-config --cflags` `xml2-config --libs`

% ./parse1 sample.xml


### Reference <br/>
- https://gitlab.gnome.org/GNOME/libxml2/

