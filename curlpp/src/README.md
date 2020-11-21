src - curlpp
===============

curlpp Sample <br/>


### sample code
- http_client.cpp <br/>
 simple HTTP Client <br/>
get from example.com <br/>
- https_client.cpp <br/>
 simple HTTPS Client <br/>
get from example.com <br/>
- http_post.cpp <br/>
HTTP Post Client <br/>
post to postman echo server <br/>

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


### Reference <br/>
- https://github.com/jpbarrette/curlpp

