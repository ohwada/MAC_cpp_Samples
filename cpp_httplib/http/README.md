http - cpp_httplib
===============

cpp_httplib sample <br/>
HTTP client and server <br/>



## sample code
- http_client.cpp <br/>
HTTP client <br/> 
- http_server.cpp <br/>
HTTP server <br/>


build sample code<br/>
% g++ http/http_server.cpp -std=c++11 -o server  <br/>

run sample code <br/>
usage: ./server [port] <br/>

display as below <br/>
> The server started at port 8080... <br/>

access localhost:8080 by WEB Brawser <br/>
<img src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/cpp_httplib/screenshot/chrome_http_server.png" width="300" />

access localhost:8080/imafe.jpg  by WEB Brawser  <br/>
<img src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/cpp_httplib/screenshot/chrome_http_server_image.png" width="300" />

### Reference <br/>
- https://github.com/yhirose/cpp-httplib 
- https://github.com/ohwada/MAC_cpp_Samples/blob/master/http.md

