#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>


int main(int argc, char** argv) {
    int i,j,n=0;
    long int N=1000000,in=0;
    double PI = 3.141592653589793238462643,pi;
    double x,y,d;
    int inpts[4];
    
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // Initialize the random generator
    srand(time(NULL));   // should only be called once
    
    // Generate a random point P(x,y) with 0<x<1 and 0<y<1
    for(i=0;i<N;i++){
        x = (double)rand()/RAND_MAX; 
        y = (double)rand()/RAND_MAX;
    
        d = sqrt(x*x + y*y);
    
        //printf("%f, %f %f\n", x,y,d);
        
        // Count the number of points inside the section
        if(d < 1.0){
            in++;
        }
    
    }
    
    inpts[n] = in;
    n++;
    
    
    //ierr = MPI_Comm_rank(MPI_COMM_WORLD, &im_id);
    //ierr = MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

      printf("I'm process %i out of %i processes\n", 
         world_rank, world_size);
         
      printf("[%d, %d, %d, %d]",inpts[0],inpts[1],inpts[2],inpts[3]);

    
    // Calculate PI and print out the approximation and the error
    pi = 4.0*(double)in/N;
    printf("Pi approximation is: %f Error: %f\n",pi,PI-pi );
    
    MPI_Finalize();
    return 0;
}
