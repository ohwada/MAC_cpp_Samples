ex_lock - berkeley-db
===============

berkeley-db exsamples <br/>

### ex_lock

Using the lock manager for non-Berkeley DB dataThe lock manager is very flexible, and can protect more than just Berkeley DB databases.  <br/>
If your application suite consistently makes read and write requests to the lock manager, it can manage access to items outside of the domain of Berkeley DB, such as URLs or read-world items. <br/>
This example uses read and write locks to control access to any kind of named object. To see how this works, run two or more instances of this interactive program, in separate terminal emulator windows. <br/>
By giving (object-name, lock-mode) pairs to the prompts you can observe when the requests are granted immediately or when they are delayed until conflicting locks are released. <br/>

build code <br/>

> % gcc ex_lock.c  `pkg-config --cflags --libs libdb`  <br/>

run code <br/>

(1) Terminal 1 locks "test"

> % ./a.out <br/>
> Operation get/release [get]> 
> input object (text string) to lock> test
> lock type read/write [read]> write
> Lock #0 granted

(2) Terminal 2 cannot lock "test"

> % ./a.out
> Operation get/release [get]> 
> input object (text string) to lock> test
> lock type read/write [read]> write
> ex_lock: : BDB0069 DB_LOCK_NOTGRANTED: Lock not granted

(3) Terminal 1 release "test"

> Operation get/release [get]> release
> input lock to release> test
> Lock #0 released

(4) Terminal 2 can lock "test"

> Operation get/release [get]> 
> input object (text string) to lock> test
> lock type read/write [read]> write
> Lock #0 granted


### Reference
- - https://github.com/berkeleydb/libdb <br/>

