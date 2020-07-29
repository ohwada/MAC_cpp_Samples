signal
===============

C signal sample <br/>

catch and handle POSIX signals <br/>

### signal.c
catch and handle signals using signal API <br/>

build code  <br/>
% gcc signal.c -o signal <br/>

run code <br/>
% ./signal <br/>

display as below <br/>
pid: 51446 <br/>
can't catch SIGKILL  <br/>
ERR: 22 Invalid argument <br/>
can't catch SIGSTOP <br/>
ERR: 22 Invalid argument <br/>
 loop <br/>
 


### sigaction.c
catch and handle signals using signaction API <br/>

build code  <br/>
% gcc sigaction.c -o sigaction  <br/>

run code  <br/>
Usage: ./sigaction [mode] <br/>
ex) <br/>
% ./sigaction <br/>

display as below <br/>
Signal: 0x102a6f970 <br/>
 loop <br/>

### kill.c
send signal using kill API <br/>

build code  <br/>
% gcc kill.c -o kill  <br/>

run code  <br/>
Usage: ./kill \< pid \> <br/>


### send signal
- SIGINT: <br/>
 CTRL+c <br/>

- SIGQUIT: <br/>
CTRL+[\\] <br/>

SIGUSR1 <br/>
% kill -USR1 pid <br/>


### Reference <br/>
- https://uguisu.skr.jp/Windows/c_signal.html
- http://doi-t.hatenablog.com/entry/2014/02/15/020909

