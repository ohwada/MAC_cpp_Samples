tidy-html5: src
===============


### samples
- sample.c <br/>
simple sample <br/>

- tidy.c <br/>
source code of command tidy <br/>

Build and Run <br/>
% make sample <br/>
or <br/>
% gcc sample.c -o sample `pkg-config --cflags --libs tidy` <br/>

% ./sample <br/>
> Tidying:	<title>Foo</title><p>Foo! <br/>
> line 1 column 1 - Warning: missing <!DOCTYPE> <br/> 
> Tidy found 2 warnings and 0 errors! <br/>


