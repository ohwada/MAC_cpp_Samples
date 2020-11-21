examples - curlpp
===============

curlpp Sample <br/>

The files in this directory are modified versions of  downloaded from below <br/>
- https://github.com/jpbarrette/curlpp/tree/master/examples <br/>

### sample code
- ex00_http_get.cpp <br/>
// The most simple http get example  <br/>
- ex01_options.cpp <br/>
This example is made to show you how you can use the Options  <br/>
- ex02_upload.cpp <br/>
an upload example <br/>
- ex03_verbose_callback_1.cpp  <br/>
verbose callback example  <br/>
- ex04_getInfo.cpp <br/>
GetInfo example <br/>
- ex05_write_function.cpp <br/>
Function functor for WriteFunction example <br/>
- ex06_writer_memory_class.cpp <br/>
 Method functor for WriteFunction example <br/>
- ex07_cookies.cpp <br/>
Cookie interface example via getInfo <br/>
- ex08_verbose_callback_2.cpp <br/>
verbose callback example, with exception safe handling <br/>
- ex09_verbose_callback_3.cpp <br/>
verbose callback example, with exception safe handling, without raiseException function <br/>
- ex10_write_file_binded.cp <br/>
Binded function functor for WriteFunction example <br/>
- ex11_write_file_plain.cpp <br/>
 Plain write function example <br/>
- ex12_http_post.cpp <br/>
HTTP POST example <br/>
- ex13_multi_interface.cpp <br/>
Simple Multi interface example <br/>
- ex15_no_value_option.cpp <br/>
Simple example for demonstrating the NoValueOptionTrait. (SslEngineDefault) <br/>
- ex16_http_post_basic_auth.cpp <br/>
HTTP POST example with HTTP Basic Authentification <br/>
- ex17_write_binded.cpp <br/>
Binded method functor for WriteFunction example <br/>
- ex20._iostream.cpp <br/>
 std::ostream usage <br/>
- ex21_upload_istream.cpp <br/>
 upload example with std::istream <br/>
- ex22_real_easy.cpp <br/>
Real easy and quick examples <br/>
- ex23_request_options.cpp <br/>
Setting request options using iterators to custom container of curlpp options <br/>
- ex24_debug_function.cpp <br/>
Binded method functor for DebugFunction example <br/>
- example14.cpp <br/>
Multi interface example with info function example <br/>
- example18.cpp <br/>
No longer available  <br/>
- example19.cpp <br/>
Multipart/formdata HTTP POST example <br/>

build code <br/>
% g++ ex00_http_get.cpp -std=c++11  `pkg-config --cflags --libs curlpp` <br/>

run code <br/>
% ./a.out <br/>

display as below <br/>
> \< title \>Example Domain \</ title \>

% ./a.out > result.html <br/>
created result.html <br/>


### Reference <br/>
- https://github.com/jpbarrette/curlpp

