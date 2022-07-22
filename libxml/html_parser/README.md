libxml: html parser
===============

HTML Parser <br/>

### samples
- html_parser1.cpp <br/>
display "a" tag and "href" content <br/>

- html_parser2.cpp  <br/>
parse while downloading <br/>


Require: <br/>
- libxml <br/>
- curl (html_parser2.cpp) <br/>


Build and Run <br/>
% make parser1 <br/>


 % ./parser1
> node: a
> attr: href
> attr value: https://www.google.com/
> a href: google


