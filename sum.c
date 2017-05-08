#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>
#include <time.h>
 
int main(int argc, char* argv[]){

int id,np;
unsigned long long int N,total=0;
double eTime,sTime,pTime;

MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &id);
MPI_Comm_size(MPI_COMM_WORLD, &np);
 
if( argc !=2){
    if (id==0){
        fprintf(stderr,"Incorrect number of arguments\n");
        fflush(stderr);
    }
    MPI_Abort(MPI_COMM_WORLD,1);
}
 
sscanf(argv[1], "%llu", &N);




MPI_Barrier(MPI_COMM_WORLD);
sTime = MPI_Wtime();

unsigned long long i;
unsigned long long int sN = id*N/np + 1;
unsigned long long int lN = (id+1)*N/np;
unsigned long long int sum = 0;



for(i = sN; i<=lN;i++){
    sum += i;
}
//printf("rank: %i of max %i sN: %llu lN: %llu Sum: %llu\n",id,np,sN,lN,sum);

//MPI_Allreduce(&lhit,&hit,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
MPI_Allreduce(&sum,&total,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);


MPI_Barrier(MPI_COMM_WORLD);
 
eTime = MPI_Wtime();
pTime = fabs(eTime - sTime);
 
if (id == 0) {
    printf("Number of Points Used: %llu\n",N);
    printf("Number of Points Used for each loop: %llu\n",lN);
    printf("Estimate of total sum: %llu\n",total);
    printf("Elapsed Wall time: %5.3e\n",pTime);
}
 
MPI_Finalize();
return 0;
}

 
