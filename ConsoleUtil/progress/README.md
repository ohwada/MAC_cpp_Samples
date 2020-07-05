progress - ConsoleUtil
===============

C++ progress sample <br/>
display progress in stdout <br/>

### progress_counter.c
the number will count up in the same line <br/>

build code  <br/>
% gcc progress_counter.c -o counter  <br/>

run code <br/>
% ./counter <br/>

display as below  <br/>
[1 / 100] <br/>

mber will count up in the same line <br/>

build code  <br/>
% gcc progress_counter.c -o counter  <br/>

run code <br/>
% ./counter <br/>

display as below  <br/>
[1 / 100] <br/>

### progress_bar.c
number will count up in the same line  like bar <br/>

build code  <br/>
% gcc progress_bar.c -o bar  <br/>

run code <br/>
% ./bar <br/>

display as below  <br/>
'####'  <br/>

### progress_roting.c
display the following characters in the same line, as rotating <br/>
 '-', '\', '|', '/' </br>

build code  <br/>
% gcc progress_roting.c -o roting  <br/>

run code <br/>
% ./roting <br/>

display as below  <br/>
'/'  <br/>

### progress_combination.c
display  progress bar and counter <br/>

build code  <br/>
% gcc progress_combination.c -o combination <br/>

run code  <br/>
% ./combination <br/>

display as below  <br/>
0%       50%       100% <br/>
+---------+---------+ <br/>
###### <br/>
50% <br/>

### reference
- https://www.mm2d.net/main/prog/c/console-01.html

