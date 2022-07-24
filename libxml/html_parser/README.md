libxml: html parser
===============

HTML Parser <br/>

### samples
- html_parser_file.cpp <br/>
display "a" tag and "href" content <br/>

- html_parser_url.cpp  <br/>
parse while downloading <br/>


Require: <br/>
- libxml <br/>
- curl (html_parser_url.cpp) <br/>


Build and Run <br/>
% make file <br/>


 % ./file
> node: a
> attr: href
> attr value: https://www.google.com/
> a href: google


