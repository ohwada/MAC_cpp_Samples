thread: src_c
===============

C Sample <br/>
run two threads <br/>

### samples
- thread.c
calculates the 40th power of 40 integers from 0 to 39 and stores the result in an array

- tiny_race.c
detects data races with ThreadSanitizer <br/>


build code
%  gcc thread.c -o thread -lpthread 

run code <br/>
% ./thread <br/>
> thread 0 
> 0 
> 1 
> 16 



