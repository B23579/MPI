#include<iostream> 
#include<mpi.h>
#include<random>

int main( int arg, char **argv)
{
	int cols=8, rank, size;

	MPI_Init(&arg, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	
	int root_rank =0;

	double *table= new double[cols];
	double *tab = new double[cols];

	if(rank == root_rank)
	{
	
	

	srand(24);	

	for(int i=0; i<cols; i++)
	{
	
		table[i] =double( rand())/double(RAND_MAX);
	}

	MPI_Send(table,cols,MPI_DOUBLE,1,1,MPI_COMM_WORLD);
	delete[] table;
	}
	
	else{

	MPI_Recv(tab,cols,MPI_DOUBLE,0,1,MPI_COMM_WORLD,0);

        std::cout<<"My rank is " << rank << std::endl; 			

	for(int  i=0;i<cols;++i){
		std::cout<< tab[i]<< std::endl;}

	delete[] tab;

	}

	MPI_Finalize();
	
	return 0;

}
