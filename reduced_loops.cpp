#include<iostream>
#include<mpi.h>

int main(int arg , char **argv) 
{

	MPI::Init(arg, argv);

	// get the number of process and the id of this process
	int rank = MPI::COMM_WORLD.Get_rank();
	int nprocs= MPI::COMM_WORLD.Get_size();

	// We want to perform 1000 iterations in total. Work out the number of iterations to perform per process...
	int count = 1000 /nprocs; 

	// we use the rank of this process to work out which iterations to perform. 

	int start = rank*count;
	int stop = start+ count ;

	// now perform the loop 

	int nloops =0; 

	for(int i=start;i<stop;++i){++nloops;}
	std::cout << "Process " << rank << " performed " << nloops << " iterations of the loop. \n";
	
	int total_nloops=0;
	MPI::COMM_WORLD.Reduce( &nloops, &total_nloops, 1, MPI_INT,MPI_SUM,0); /* this function reduces the data in message
		 pointed by nloops using the MPI operation MPI_SUM and places the resulting message into total_nloops
	the message is the size of 1, the data type is int specify by MPI_INT, the resulting message is
 	placed only into received on the process whose rank is given by 0. The MPI_Reduce will send
 	the result back to only the designated process(which should normaly be our master note)*/
		

	if(rank==0){ 
		// are there any more loops to run?
		nloops = 0;

		for(int i=total_nloops; i<1000;++i){ ++nloops;}
		std::cout << "Process 0 perform the remaining " << nloops << " iterations of the loop \n";
		}
	MPI::Finalize();

	return 0;
}

// compile the code using mpicxx reduced_loops.cpp -o reduced_loops.cpp
// run the code using mpirun -np x reduced_loops where x represent the number of process or core 
