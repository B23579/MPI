#include<iostream>
#include<mpi.h>

int main(int argc , char **argv){
	
	MPI::Init(argc, argv);

	// get the number of process and the id of this process
	int rank= MPI::COMM_WORLD.Get_rank();
	int nproc =MPI::COMM_WORLD.Get_size(); // return the number of the process in the MPI team.

	//we want to perfom 1000 iterations in total. Work out the number of iterations to perform per process..
	int count = 1000/nproc;

	// we use the rank of this process to work out which iterations to perform.
	
	int start = rank*count;
	int stop = start + count ; 
	
	// now perform the loop
	int nloops = 0;
	for(int i= start; i<stop; ++i){ ++nloops;}
	std::cout<<" Process " << rank << " Performed " << nloops << " iterations of the loop. \n";

	MPI::Finalize();

	return 0;
	

}
