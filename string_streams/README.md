StringStreams
===============

StringStreams sample <br/>

StringStreams : <br/>
the fmemopen and open_memstream functions allow you to do I/O to a string or memory buffer. 
- https://www.gnu.org/software/libc/manual/html_node/String-Streams.html

## sample code
- fmemopen.c 
open memory as stream
- open_memstream <br/>
open a dynamic memory buffer <br/>
 

build sample code<br/>
% gcc fmemopen.c <br/>

run sample code <br/>
% ./a.out  <br/>

display as below <br/>
> buffer: foobar <br />
> Got f  <br/>
> Got o  <br/>
> Got o  <br/>


### Reference <br/>
- https://www.gnu.org/software/libc/manual/html_node/String-Streams.html

