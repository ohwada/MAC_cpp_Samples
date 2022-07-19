feed-reader-lib
===============

This is Clone <br/>
 https://github.com/purcaro/feed-reader-lib <br/>

Changes <br/>
changed Makefile <br/>
so that it can built on Mac <br/>
minor changes to eliminate complie errors <br/>


### About:
 Fast, thread-safe, extensible &amp; platform independent feed reader library in C++, <br/>
supports RSS, ATOM, RDF <br/>

### Dependencies:
- Boost >=1.55 <br/>
- libcurl > 7.18.1 <br/>
- Xerces > 2.8.0 <br/>
- Xalan > 1.10.1 <br/>
- Zlib > 1.23 <br/>
- OpenMP <br/>

setup.py: download libraries <br/>

### Build and Run:
% make <br/>
build with examples/feed_reader_tester.cpp <br/>
created bin/FeedReaderTester <br/>

% cd bin <br/>
 % ./FeedReaderTester < feed_url > <br/>
Note: require ../xsl/RSS_20_xsl.xml <br/>

 % ./FeedReaderTester https://rss.nytimes.com/services/xml/rss/nyt/World.xml <br/>
> ---------Feed---------  <br/>
> URL: 'https://rss.nytimes.com/services/xml/rss/nyt/World.xml' <br/>
> title:	'NYT > World News' <br/>
> url: 'https://www.nytimes.com/section/world' <br/>


