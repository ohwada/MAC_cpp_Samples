libomp: openmp-examples
===============

This is Clone <br/>
https://github.com/muatik/openmp-examples <br/>

Changes: <br/> 
added Makrfile, <br/>
so that it can build on Mac <br/>


### About:
This repository contains OpenMP-examples <br/>

### Details:
- hello-mp <br/>
Hello world in open-mp <br/>

- parallel-loop-1 <br/>
traversing a loop in parallel <br/>

- avrage-reduction <br/>
	calculating avg by using atomic and reduction concepts <br/>

- heap-vs-stack <br/>
sharing(global) and not sharing data(local) between threads. <br/>

data-sharing  <br/>
private, first-private, initialization concepts <br/>

- integral	<br/>
calculating integral in various ways to demonstrate approaches <br/>

- scheduling	 <br/>
thread scheduling

linkedlist	<br/>
consuming linkedlist in multiple threads in a thread-safety way <br/>

- Als	<br/>
movie recommender system using alternating least squares method <br/>


### Build and Run:
Require : <br/>
- libomp <br/>
- eigin (optional) <br/>

% make <br/>

% ./hello_mp <br/>
> hello  0 <br/>
> hello again 0 <br/>
> hello  1 <br/>
> hello again 1 <br/>
> hello  2 <br/>
> hello  3 <br/>
> hello again 3 <br/>
> hello again 2 <br/>


