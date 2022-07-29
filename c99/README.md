c99
===============


### Whats New in C99  

Reference:    
- https://en.cppreference.com/w/c/99  
- https://www.buildinsider.net/language/clang/01  

Samples:  

 - variable.c  
 variable declarations  
https://kaworu.jpn.org/c/C99%E3%81%AEfor%E3%83%AB%E3%83%BC%E3%83%97%E3%81%AF%E3%82%A4%E3%83%B3%E3%83%A9%E3%82%A4%E3%83%B3%E3%81%A7%E3%82%AB%E3%82%A6%E3%83%B3%E3%82%BF%E3%81%AE%E5%A4%89%E6%95%B0%E3%82%92%E5%AE%A3%E8%A8%80%E3%81%A7%E3%81%8D%E3%82%8B


- array.c  
variable length array   

- bool.c  
bool type  

- snprintf.c  
snprintf  

- coment.c  
c++ style comment  


### BUild and Run  
  
(1) normal (c99)  
% make variable  
or  
% gcc variable.c    

(2) ANSI-C   
%make ansi_variable  
or  
 % gcc variable.c -ansi -Wall -Werror  

% ./variable
 > sum = 45 


