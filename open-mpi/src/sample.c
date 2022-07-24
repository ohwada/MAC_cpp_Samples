/**
 * sample.c
 * 2022-06-01 K.OHWA
 */

// show myself rank and the host name running myself
// reference : https://qiita.com/kkk627/items/49c9c35301465f6780fa

#include <stdio.h>
#include <mpi.h>


/**
 * main
 */
int main(int argc, char **argv)
{
 const  int BUFSIZE = 10;
  char *name[BUFSIZE]; // host name
  int rank; // rank
  int proc; // total number of processes
  int name_length; // hostname length

// initialization of MPI
  MPI_Init(&argc, &argv);
// get rank
  MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
// get the total number of processes
  MPI_Comm_size(MPI_COMM_WORLD, &proc);   
// get the host name
 MPI_Get_processor_name( (char *)name, &name_length); 


// show results
  printf("%s : %d of %d\n", (char *)name, rank, proc); 
 
// MPI termination process
  MPI_Finalize();

  return 0;
}


