libzip: src
===============

### sample
- show_zip.c  


Build and Run:  
% make  
or  
 gcc show_zip.cpp -o show `pkg-config --cflags --libs libzip`   

% ./show  
> num: 4  
> i: 0 , name: sample/sample1.txt   
> i: 1 , name: sample/sample2.txt   
> i: 2 , name: sample/sample3.txt   
> i: 3 , name: sample/   
