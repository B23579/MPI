#include<iostream>
#include<mpi.h>
#include<unistd.h> // this has being included to use the function sleep 

// The function if will be used to control which function is called by which process in the MPI process team. 

void times_table(int n)
{

	int rank = MPI::COMM_WORLD.Get_rank(); // this return the rank of the calling process
	
	for (int i=1;i<=n; ++i)
	{
		int i_times_n = i*n;
		std::cout<< "Process " << rank <<" says "<< i << " times "<< n<< " equals " << i_times_n << std::endl;
		sleep(1); //to add one second pause 
	}
	
}


void count_down() 
{
	int rank = MPI::COMM_WORLD.Get_rank();

	for (int i=10; i>=1; --i){

		std::cout<<"Process "<< rank <<" says " << i << "...\n";
		sleep(1);
	}

	std:: cout << "Process " << rank << " says \"Lift off!\"n";

}

void long_loop()
{
	double sum= 0;
	int rank =MPI:: COMM_WORLD.Get_rank();

	for (int i=1; i<=10;++i)
	{
		sum +=(i*i);
		sleep(1);
	}
	
	std::cout<<"Process " << rank<<" says the sum of the long  loop is " << sum << std::endl;

}



int main(int argc, char **argv){


	MPI::Init(argc,argv);

	int rank = MPI::COMM_WORLD.Get_rank();

	if(rank==0){

		std::cout<<"This is the main process \n ";
		times_table(12);
		}
	else if (rank=1){
			count_down();
			}
	else if(rank=2){ long_loop();}
	else { std::cout<<"I am not needed ...\n";}

	MPI::Finalize();

	return 0;


}




























