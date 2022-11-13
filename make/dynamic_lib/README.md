make: dynamic lib
===============

make hello with  dynamic shared libraly  

### sample code  
- main.c  

Build and Run:  
% make hello  
created lib/libhello.dylib  

% bin/hello  
> Hello World  


otool  
https://www.manpagez.com/man/1/otool/  


(1) own path of shared library  
% otool -D libhello.dylib  
> libhello.dylib: lib/libhello.dylib  

(2) paths of dependent libraries  
% otool -L libhello.dylib  
> lib/libhello.dylib  
> /usr/lib/libSystem.B.dylib  

(3) paths of dependent libraries of executable file  
% otool -l hello  
> name /usr/lib/dyld   
> name lib/libhello.dylib   
> name /usr/lib/libSystem.B.dylib 


### Document  
https://ken-ohwada.hatenadiary.org/entry/2022/11/13/130833  


