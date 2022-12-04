system:  byte order
===============


 Byte order(or Endianness ) :    
In computing, endianness is the order or sequence of bytes of a word of digital data in computer memory.  
https://en.wikipedia.org/wiki/Endianness  

SByteOrder.h:   
https://opensource.apple.com/source/xnu/xnu-344.2/libkern/libkern/OSByteOrder.h.auto.html  


### samples
- byte_order.c
- byte_swap.c

Build and Run: 
% make order  
% bin/order
> 7f000001 
> 01,00,00,7f 
 
