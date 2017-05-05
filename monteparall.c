#include "mpi.h"
#include <stdio.h>
#define SIMPLE_SPRNG        /* simple interface  */
#define USE_MPI             /* use MPI           */
//#include "sprng.h"          /* SPRNG header file */
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define BATCHSIZE 1000000

int main( int argc, char *argv[] )
{
    int i, j, numin = 0, totalin, total, numbatches, rank, numprocs;
    double x, y, approx, pi = 3.141592653589793238462643;

    srand(time(NULL));   // should only be called once
  
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes

    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    
  
  
    //MPI_Init( &argc, &argv );
    //MPI_Comm_size( MPI_COMM_WORLD, &numprocs );
    //MPI_Comm_rank( MPI_COMM_WORLD, &rank );  
    

    if ( rank == 0 ) {
        numbatches = atoi( argv[1] );
    }
    MPI_Bcast( &numbatches, 1, MPI_INT, 0, MPI_COMM_WORLD );
    for ( i = 0; i < numbatches; i++ ) {
        for ( j = 0; j < BATCHSIZE; j++) {
            //x = sprng( ); y = sprng( );
            x = (double)rand()/RAND_MAX; 
            y = (double)rand()/RAND_MAX; 
            if ( x * x + y * y < 1.0 )
                numin++;
        }
        MPI_Reduce( &numin, &totalin, 1, MPI_INT, MPI_SUM, 0,
                    MPI_COMM_WORLD );
        if ( rank >= 0 ) {
            total = BATCHSIZE * ( i + 1 ) * numprocs;
            approx = 4.0 * ( (double) totalin / total );
            printf( "pi = %.16f; error = %.16f, points = %d\n",
                    approx, pi - approx, total );
        }
    }
    
    MPI_Finalize();
    return 0;
}
