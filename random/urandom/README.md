random: urandom
===============

read random number from /dev/crandom

/dev/random:  
 /dev/random and /dev/urandom are special files  
 that serve as cryptographically secure pseudorandom number generators.  
 https://en.wikipedia.org/wiki//dev/random  


### sample
- urandom.c

Build and Run:
% make
% bin/crandom
> a5 dd 43 9b 
