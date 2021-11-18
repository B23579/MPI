#include<iostream>
#include<mpi.h>

int main(int arg, char **argv){
	 MPI::Init(arg,argv);

	// get the number of process, and the id of the process

	int rank = MPI::COMM_WORLD.Get_rank();
	int nprocs = MPI::COMM_WORLD.Get_size();



	// we want to perform 1000 iterations in total Work out the number of iterations to perfrom per process...


	int count = 1000 / nprocs; 
	
	// we use the rank of this process to work out which iterations to perform 

	int start = rank*count;
	int stop = start + count; 


	// now perform the loop

	int nloops= 0;

	for (int i=start; i<stop; ++i){ ++nloops;}
	
	std::cout<< "Process " << rank << " performed " << nloops << " iterations of the loop.\n"; 

	if(rank !=0 ) {

		//if we are not the master process ( rank 0) then we need to tell hat process how many iterations we performed.
		MPI::COMM_WORLD.Send(&nloops,1, MPI_INT, 0,0); /*this function send the message in the memory pointed to by nloops in the curent process
								to the process whose rank is given  by 0, 
								*/
	
	}
	
	else 
	{
		// if we are the master process, then we need to wait to be told how many iterations were performe by each other process 

		int total_nloops = nloops;

		for (int i=1;i<nprocs;++i){
					
			MPI::COMM_WORLD.Recv(&nloops,1,MPI_INT,i,0); // we are receiving ain integer from a process i,and save it in nloops in the master process
			total_nloops += nloops; /* This function receives the massage from the process whose rank is given in i. the message is placed into the memery pointed to by 
						nloops, 1 is the number of integers send 


						*/

					}
		// ok -are there any more loops run?
		nloops=0;

		for(int i=total_nloops;i<1000;++i){++nloops;}
		std::cout<< "Process 0 perform the remaining "<< nloops << " iterations of the loop \n";
	}

	MPI::Finalize();
	return 0;

}




















