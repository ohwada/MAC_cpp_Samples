ex_access - berkeley-db
===============

berkeley-db exsamples <br/>

### ex_access

Add lines of text to a database & display them <br/>
This simple program uses the DB->put() and DB->get() API calls to store lines of text, entered from the standard input, into a btree database. <br/>
Each key is the text as it was entered; the data is the reversed version of the key. <br/>
At EOF (or “quit”), it opens a cursor and displays each record, ordered by the key. <br/>
Since the records are DB->put() with the DB_NOOVERWRITE flag, 
the error DB_KEYEXIST is returned if you enter a key which has already been stored in the database. <br/>

build code <br/>

> % gcc ex_access.c  `pkg-config --cflags --libs libdb` <br/>

run code <br/>

> % ./a.out <br/>
> input> abc 123 <br/>
> input> def 456 <br/>
> input> exit <br/>
> abc 123 : 321 cba <br/>
> def 456 : 654 fed <br/>

created "access.db" <br/>

### Reference
- https://github.com/berkeleydb/libdb <br/>

