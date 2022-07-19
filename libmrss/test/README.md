libmrss: test
===============

samples in this directory, <br/>
downloaded from below <br/>
https://github.com/bakulf/libmrss/tree/master/test <br/>

### samples
- parser.c <br/>
 parse url_rss <br/>

- search.c <br/>
search feeds in url_rss <br/>

- time.c <br/>
get last modified in url_rss <br/>

- write.c <br/>
write url_rss to file <br/>

- new.c <br/>
for test <br/>


Buld and Run <br/>
% gcc parser.c -o parser -lmrss <br/>

% ./parser https://news.yahoo.co.jp/rss/topics/top-picks.xml <br/>


