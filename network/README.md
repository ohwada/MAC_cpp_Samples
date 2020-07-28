network
===============

C network sample <br/>
tcp server and client <br/>

## server.c
start the server <br/>
wait for connection from client <br/>

build code  <br/>
% gcc server.c -o server <br/>

run code <br/>
% ./server <br/>

display as below <br/>
waiting for connection port: 9876 <br/>
please run client program <br/>
or quit with ctrl-c <br/>

 
## client.c
connect to the server <br/>
send and receive data <br/>

build code  <br/>
% gcc client.c -o client  <br/>

run code  <br/>
% ./client <br/>

display as below <br/>
connected : 127.0.0.1 : 9876 <br/>
please enter the alphabets <br/>
\> <br/>
### Reference <br/>
- http://onishi-lab.jp/programming/tcp_linux.html

