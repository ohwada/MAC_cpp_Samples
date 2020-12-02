http - network
===============

C network sample <br/>
HTTP Client and Server <br/>

### sample code
- http_client.c <br/>
simple HTTP Client <br/>
- http_server.c <br/>
simple HTTP Server <br/>

build code  <br/>
% gcc http_client.c <br/>

run code <br/>
Usage: ./a.out  [host] [port]
% /a.out   <br/>

display as below <br/>
> Conntect to: example.com : 80 <br/>
> \<title\> Example Domain \</title\> <br/>

#### http_server.c <br/>
access localhost:8080 by WEB Brawser <br/ >
<img src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/network/screenshot/chrome_http_server.png" width="300" />

### Reference <br/>
- http://onishi-lab.jp/programming/tcp_linux.html
- https://tools.ietf.org/html/rfc7230


