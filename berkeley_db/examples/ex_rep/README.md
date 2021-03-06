ex_rep - berkeley-db
===============

berkeley-db exsamples <br/>


### ex_rep 

Replicated stock quote server <br/>
Berkeley DB supports building highly available applications via replication groups, which contain a master environment and one or more read-only clients. Replicas may be on the same machine or connected by local or wide-area networks. <br/>
The replication example is a small stock quote server.  <br/>
There are two versions of the program: <br/>
one uses Berkeley DB's Replication Manager support, <br/>
and the other uses the underlying base replication API. <br/>


(1) preparation <br/>

> % mkdir server <br/>
> % mkdir client <br/>


(2) build code <br/>

> % gcc mgr/rep_mgr.c  common/rep_common.c `pkg-config --cflags --libs libdb` <br/>



(3) run code <br/>

(3-1) run as master mode <br/>

> % ./a.out  -M -h server -l localhost:6000 <br/>
> QUOTESERVER/> <br/>

created files in server directory <br/>

(3-2) run as client mode <br/>

> % ./a.out -C -h client -l localhost:6001 -r localhost:6000 <br/>
> QUOTESERVER (read-only)\> ex_rep_mgr: ignoring event 7 <br/>
> ex_rep_mgr: ignoring event 7 <br/>
> ex_rep_mgr: ignoring event 12 <br/>

created files in client directory <br/>


### Reference
- https://github.com/berkeleydb/libdb <br/>

