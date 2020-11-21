curlpp
===============

curlpp Sample <br/>

curlpp : <br/>
cURLpp is a C++ wrapper for libcURL <br/>
http://www.curlpp.org/ <br/>


###  install curlpp
see below <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/curlpp/setup <br/>


### sample code
- http_client.cpp <br/>
 simple HTTP Client <br/>
- https_client.cpp <br/>
 simple HTTPS Client <br/>
- http_post.cpp <br/>
HTTP Post Client <br/>

- http_to_file.cpp <br/>
get web page from example.com, save to local file <br/>
- http_to_memory.cpp <br/>
get web page from example.com, copy to memory <br/>
- http_post_to_file.cpp <br/>
http post to postman echo server,  save response to local file
- http_post_to_memory.cpp <br/>
http post to postman echo server,  copy response to memory <br/>
- version.cpp <br/>
display version <br/>


build code <br/>
% g++ src/http_client.cpp -std=c++11  `pkg-config --cflags --libs curlpp` <br/>

run code <br/>
% ./a.out <br/>

display as below <br/>
> \< title \>Example Domain \< /title \>


### examples
downloaded from below <br/>
- https://github.com/jpbarrette/curlpp/tree/master/examples <br/>


### Reference <br/>
- https://github.com/jpbarrette/curlpp

