libomp
===============

libomp: <br/>
LVM's OpenMP runtime library <br/>
https://openmp.llvm.org/ <br/>

LVM:  <br/>
LVM( Logical Volume Management)
 provides a method of allocating space on mass-storage devices that is more flexible than conventional partitioning schemes to store volumes. <br/>
https://en.wikipedia.org/wiki/Logical_volume_management

OpenMP: <br/>
OpenMP (Open Multi-Processing) is  application programming interface (API) <br/>
that supports multi-platform shared-memory multiprocessing programming in C <br/>
https://en.wikipedia.org/wiki/OpenMP <br/>


## install
% brew install libomp <br/>
https://formulae.brew.sh/formula/libomp <br/>
% ls /usr/local/include/omp*   <br/>
% ls /usr/local/lib/libomp*   <br/>


## OpenMP on Mac
 Apple Clang does allow you to process the OpenMP pragmas with <br/>
-Xpreprocessor -fopenmp   <br/>

HighSierraのOpenMP   <br/>
https://iscinumpy.gitlab.io/post/omp-on-high-sierra/   <br/>


## openmp-examples
- hello-mp
- als-movie-recommender
- avrage-reduction
- data-sharing
- heap-vs-stack
- integral
linkedlist
- parallel-loop-1
- scheduling


### Reference
- https://openmp.llvm.org/

