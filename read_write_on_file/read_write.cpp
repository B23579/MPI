#include<iostream>
#include<fstream>
#include<mpi.h>

int main(int arg, char** argv)
{
	std::fstream myFile;	

	int size, rank;

	MPI_Init(&arg,&argv);

	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	myFile.open("test.csv", std::ios::app);  //append mode

	if (myFile.is_open())
	{
		myFile<< rank<< ";" << size << std::endl;
		myFile.close();
	}
		
	MPI_Finalize();
	
	return 0;
}
