libxml++: rss parser
===============

RSS Parser <br/>
extract the Title from RSS Feeds  <br/>

Sample Feeds <br/>
https://www.feedforall.com/sample-feeds.htm <br/>

Build and Run <br/>
% g++  rss_parser.cpp -std=c++11 `pkg-config --cflags --libs libxml++-2.6` -o rss <br/>

% ./rss sample.xml <br/>
> Title: RSS Solutions for Restaurants <br/>
> Title: RSS Solutions for Schools and Colleges <br/>


