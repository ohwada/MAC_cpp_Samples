filesystem:  recursive_directory
===============


recursive_directory_iterator:  
It is a LegacyInputIterator that iterates over the directory_entry elements of a directory, and, recursively, over the entries of all subdirectories.   
https://en.cppreference.com/w/cpp/filesystem/recursive_directory_iterator  

LegacyInputIterator: 
It is a LegacyIterator that can read from the pointed-to element.   
https://en.cppreference.com/w/cpp/named_req/InputIterator  

LegacyIterator:
It requirements describe types that can be used to identify and traverse the elements of a container.  
https://en.cppreference.com/w/cpp/named_req/Iterator  


### samples
- recursive_show_file.cpp
Show file in directory recursivily

- recursive_file_size.cpp
Computing the size of a directory

- recursive_last_write_time.cpp
Showing files older than a given date

- recursive_find_file.cpp
Finding files in a directory that match a regular expression


Buid and Run:  
% make show

% bin/show 
> "./test"  
> "./test/wct123.txt"  
> "./test/.DS_Store"  
> "./test/wctABC.tmp"  
> "./test/1st"  


