# feed-reader-lib
Fast, thread-safe, extensible &amp; platform independent feed reader library in C++, supports RSS, ATOM, RDF

## Features

In FeedReader, all feeds are transformed via XSL to a uniform schema before being parsed.
This means that in order to extend FeedReader to support a new feed format, all that is needed is a new XSL file.
The library comes with XSL files supporting for the following feed formats:

    * RSS 1.0
    * RSS 2.0
    * ATOM 0.3
    * ATOM 1.0
    * RDF

An iterator interface is provided to the feed elements parsed.

Using the library is simple and sample client code is located in the examples directory.

## Dependencies

The FeedReader library is dependent on, and was tested with the following libraries/versions:

    * GCC >= 4.7 (tested with 4.8 on Ubuntu 12.04)
    * Boost >=1.55 (can be built using setup.py; tested on Ubuntu 12.04)
    * libcurl > 7.18.1
    * Xerces > 2.8.0
    * Xalan > 1.10.1
    * Zlib > 1.23 (required by CURL)

## History
* FeedReader was created by Yoav Aviram (yoav.aviram AT gmail DOT com)
* FeedReader was migrated to GitHub by Michael Purcaro (purcaro AT gmail DOT com)

   converted from https://code.google.com/p/feed-reader-lib/ by
   * git svn clone --stdlayout --no-metadata -A authors  http://feed-reader-lib.googlecode.com/svn/
   * git remote add origin git@github.com:purcaro/feed-reader-lib.git
   * git config branch.master.remote origin
   * git config branch.master.merge refs/heads/master
   authors.txt file:
   * (no author) = no_author <no_author@no_author>
   * yoav.aviram = Yoav Aviram <yoav.aviram@gmail.com>
