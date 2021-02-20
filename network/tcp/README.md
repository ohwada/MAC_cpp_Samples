tcp - network
===============

C network sample <br/>
TCP Client and Server  using socket functions <br/>

### sample code
- tcp_echo_client.c <br/>
TCP Client for Echo server <br/>
- tcp_echo_server.c <br/>
TCP Echo Server <br/>

- tcp_interactive_client.c <br/>
TCP Client for toupper server <br/>
- tcp_toupper_server.c <br/>
TCP Server <br/>
 convert the string sent from the client to uppercase and send it back <br/>


build code  <br/>
% gcc tcp_echo_server.c -o server <br/>

run code <br/>
% /server   <br/>

display as below <br/>
> waiting for connection port: 9876   <br/>

### Document
- https://ken-ohwada.hatenadiary.org/entry/2021/02/20/111624

### Reference <br/>
- http://onishi-lab.jp/programming/tcp_linux.html

