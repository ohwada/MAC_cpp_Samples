open-mpi
===============

open-mpi: <br/>
High performance message passing library <br/>
https://www.open-mpi.org/ <br/>

Open MPI: <br/>
Open MPI(Message Passing Interface) is Library Project combining technologies <br/>
https://en.wikipedia.org/wiki/Open_MPI <br/>


### install
% brew install open-mpi <br/>
https://formulae.brew.sh/formula/open-mpi <br/>

% pkg-config --cflags --libs ompi <br/>
> -I/usr/local/Cellar/open-mpi/4.1.4/include <br/>
> -L/usr/local/Cellar/open-mpi/4.1.4/lib <br/>
> -L/usr/local/opt/libevent/lib <br/>
> -lmpi <br/>

% mpicc -v <br/>
> Apple clang version 12.0.0 (clang-1200.0.32.29) <br/>
> Target: x86_64-apple-darwin19.6.0 <br/>
> Thread model: posix <br/>
> InstalledDir: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin <br/>


### src
- sample.c <br/>


### Reference
- https://www.open-mpi.org/ 

