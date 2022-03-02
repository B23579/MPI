#include<iostream>
#include<mpi.h>

int main(int arg, char** argv){


	int size, rank;

	MPI_Init(&arg, &argv);

	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	double ***A,***B ;
	int n= 3,m=7,k=7; // 3D matrix nxmxk

	// we want to perform  n x m x k addition in total for 3D matrix. n represent the number of m x k matices,
	// each process will performe addition on certain number of matrix

	int count =  n/size;

	// we use the rank of this process to work out which iterations to perfom
	int start = rank*count;
	int stop = start + count;

	A = new double**[n];
	B = new double**[n];

		// Generate a matrix A
	
	srand(23);
	
	for(int i=0; i<n;++i){

		A[i] = new double*[m];

		for(int j=0; j<m; ++j)
			{

			A[i][j]=new double[k];

			for(int l=0;l<k;l++)
			 	{

				A[i][j][l] = double(rand())/double(RAND_MAX);
				}
			}
	}
		
	/// Generate a matrix 

	srand(50);
	for(int i=0; i<n;++i){

		B[i] = new double*[m];

		for(int j=0; j<m; ++j)
			{

			B[i][j]=new double[k];

			for(int l=0;l<k;l++)
			 	{

				B[i][j][l] = double(rand())/double(RAND_MAX);
				}
			}
	}	
	

		/* A[start: stop][][] + B[start:stop][][] */
		
		for(int i= start; i<stop; i++){
			for (int j=0;j<m;j++){
				for(int l=0;l<k;l++)
					A[i][j][l]= A[i][j][l] + B[i][j][l];
						}
				}




	// delete the dynamic memory 

	for(int i=0; i<n; i++){ 
		for(int j=0; j<m; j++){delete[] B[i][j];}
		delete B[i]; }

	for(int i=0; i<n; i++){ 
		for(int j=0; j<m; j++){delete[] A[i][j];}
		delete A[i]; }

	delete B;
	delete A;
	MPI_Finalize();
	return 0;
}
