expat
===============


expat: <br/>
XML 1.0 Parser <br/>
https://libexpat.github.io/ <br/>


###  install 
% brew install expat <br/>
https://formulae.brew.sh/formula/expat <br/>

% pkg-config --cflags --libs expat <br/>
> -lexpat <br/>

### samples
- expat_test1.c <br/>
display list of elements <br/>

- expat_test2.c <br/>
 display the data in the element <br/>

- expat_test3.c <br/>
 display element name and the data in the element as a set <br/>

Build and Run <br/>
Require: <br/>
- utstring.h <br/>

% gcc expat_test1.c -Wall -lexpat -o test1 <br/>
% ./test1 < sample.xml <br/>


### Reference <br/>
- https://libexpat.github.io/
