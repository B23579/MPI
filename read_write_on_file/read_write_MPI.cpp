#include<iostream>
#include<fstream>
#include<mpi.h>
#include<string>

int main(int arg, char** argv)
{
	//std::fstream myFile;	

	int size, offset, rank, buf[0], msgsize;
	std::string msg ="Hello world";
	msgsize =12;
 
	MPI_Init(&arg,&argv);

	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	MPI_File fh;
	MPI_Status status;
	offset = rank*msgsize;

	MPI_File_open(MPI_COMM_WORLD, "test.out",MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &fh); 
	MPI_File(fh,offset,MPI_SEEK_SET);

	//myFile.open("test.csv", std::ios::app);  //append mode

	MPI_File_write(fh,msg,msgsize,MPI_CHAR,&status);

	MPI_File_close(&fh);

	MPI_Finalize();
	
	return 0;
}
