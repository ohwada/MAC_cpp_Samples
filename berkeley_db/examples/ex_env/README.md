ex_env - berkeley-db
===============

berkeley-db exsamples <br/>


### ex_env

Setting up a fully transactional environment <br/>
This shows how to set up a Transactional Data Store environment.  <br/>
It shows how to customize several parameters before opening the environment. <br/>

### TODO

This example doesn't work <br/>
display error as below <br/>
> database open: No such file or directory <br/>

### run example code <br/>

(1) preparation <br/>

> % mkdir TESTDIR <br/>

(2) build code <br/>

> % gcc ex_env.c  `pkg-config --cflags --libs libdb` <br/>

(3) run code <br/>

> % ./a.out <br/>


### Reference
- https://github.com/berkeleydb/libdb <br/>

