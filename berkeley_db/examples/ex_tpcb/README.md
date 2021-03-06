ex_tcpb - berkeley-db
===============

berkeley-db exsamples <br/>

### ex_tpcb

The TPC-B transaction processing benchmarkTPC-B is an early transaction processing benchmark that simulates bank transfers from one account to another.  <br/>
The program is first run in an initialization mode which loads the data. <br/>
Subsequent runs in one or more processes perform a workload. <br/>
Database initialization (the -i flag) and running the benchmark (-n flag) must take place separately (i.e., first create the database, then run one or more copies of the benchmark).  <br/>
When running more than one TPC-B process, it is necessary to run the deadlock detector (db_deadlock), since it is possible for concurrent processes to deadlock. <br/>


### Preparation

> % mkdir TESTDIR <br/>

### build ode

> % gcc ex_tpcb.c  `pkg-config --cflags --libs libdb`  <br/>

### run ode

(1) first create the database <br/>

> % ./a.out -i <br/>

created files in TESTDIR

(2) run one or more copies of the benchmark <br/>

>  % ./a.out -n 10 <br/>

display as below <br/>
>ex_tpcb: 10 txns: 0 failed, 0.181 sec, 55.15 TPS <br/>


### Reference
- - https://github.com/berkeleydb/libdb <br/>

