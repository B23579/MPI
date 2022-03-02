#include<iostream>
#include<mpi.h>



int main(int arg, char** argv){

	int rank, size;

	MPI_Init(&arg, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	int n= 3,m=3,k=3; // 3D matrix nxmxk

	if(rank ==0){

	double*** p;
	

	p = new double**[n];

	for(int i=0; i<n;++i){

		p[i] = new double*[m];

		for(int j=0; j<m; ++j)
			{

			p[i][j]=new double[k];

			for(int l=0;l<k;l++)
			 	{

				p[i][j][l] = rand();
				}
			}
	}


		// print out the matrix
	
	for(int i=0;i<n;++i)
	{
		for(int j=0;j<m;++j){
			for(int l=0;l<k;++l){
				std::cout<< p[i][j][l] << " " ;}
		std::cout<<"\n";}

	std::cout<<" \n";
	}
		
		// send a matrix 

	MPI_Send(p[0][0],m,MPI_DOUBLE,1,0,MPI_COMM_WORLD);	

	
	// delete the dynamic memory 

	for(int i=0; i<n; i++){ 
		for(int j=0; j<m; j++){delete[] p[i][j];}
		delete p[i]; }
	}

	else{
		double *vec= new double[m];

		MPI_Recv(vec,m,MPI_DOUBLE,0,0,MPI_COMM_WORLD,0);
		std::cout<<"My rank is " << rank <<" " <<std::endl;  
		
	
		for(int i=0; i<m; ++i)
		{	std::cout<<vec[i] << " ";}

		delete[] vec;

		}

	return 0;
}
