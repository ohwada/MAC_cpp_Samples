getopt
===============

getopt sample <br/>
parse commandline options <br/>


### sample codes
- getopt.c  <br/>
parse commandline options with getopt  <br/>
- getopt_long.c  <br/>
parse commandline options with getopt_long  <br/>


build code  <br/>
% gcc getopt.c <br/>

run code <br/
% ./a.out <br/>

display as below  <br/>
flags=0; tfnd=0; nsecs=0; optind=1 <br/>
Expected argument after options <br/>

% ./a.out -t 10 -n hoge <br/>
 flags=1; tfnd=1; nsecs=10; optind=4 <br/>
 name argument = hoge <br/>


### Reference <br/>
- https://linuxjm.osdn.jp/html/LDP_man-pages/man3/getopt.3.html

