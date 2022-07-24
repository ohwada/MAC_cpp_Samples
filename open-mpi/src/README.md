open-mpi: src
===============

### sample
- sample.c <br/>

Build anr Run: <br/>
% mpicc sample.c -o sample <br/>

% mpirun -np 2 ./sample <br/>
> MacBook-Air.local : 0 of 2 <br/>
> MacBook-Air.local : 1 of 2 <br/>

% mpirun -np 4 ./sample <br/>
> There are not enough slots available in the system to satisfy the 4 slots that were requested by the application: <br/>


