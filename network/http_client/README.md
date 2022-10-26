network: http client
===============

### sample code
- http_client.c

Build and Run:  
% make client
% bin/client
> Conntect to: example.com : 80 
> < title >Example Domain< /title >


### TODO:
(1) variable length buffer

(2) suport Transfer-Encoding: chunked
in this version
body contains unnecessary chunksize like 5e6c

