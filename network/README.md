network
===============

C network sample <br/>
TCP server and client <br/>

### sample code
- tcp_server.c
start TCPserver <br/>
wait for connection from client <br/>
- tcp_client.c
connect to TCP server <br/>
send and receive data <br/>
- http_server.c <br/>
very simple HTTP Server <br/>
- http_client.c <br/>
get web page from HTTP server <br/>


build code  <br/>
% gcc tcp_server.c -o server <br/>

run code <br/>
% ./server <br/>

display as below <br/>
waiting for connection port: 9876 <br/>
please run client program <br/>
or quit with ctrl-c <br/>



### Reference <br/>
- http://onishi-lab.jp/programming/tcp_linux.html

