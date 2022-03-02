#include<iostream>
#include<mpi.h>
#include<string.h>


struct person_t 
{
	int age;
	double height;
	char name[10];
};


int main( int argc, char* argv[])
{

	MPI_Init(&argc,&argv);

	// get the number of processes 

	int size;

	MPI_Comm_size(MPI_COMM_WORLD,&size);

	//create the datatype
	MPI_Datatype person_type; // we want to creat persone_type as data type 
	
	int lenghts[3] ={1,1,10}; // 1 for age MPI_INT, 1 for height MPI_DOUBLE and 10 for MPI_CHAR

	MPI_Aint displacements[3]; // this is use to compute the displacement. 

	struct person_t dummy_person; 
	MPI_Aint base_address;
	MPI_Get_address(&dummy_person, &base_address);
	MPI_Get_address(&dummy_person.age, &displacements[0]);
	MPI_Get_address(&dummy_person.height,&displacements[1]);
	MPI_Get_address(&dummy_person.name[0],&displacements[2]);
	displacements[0] =MPI_Aint_diff(displacements[0], base_address);
	displacements[1] =MPI_Aint_diff(displacements[1],base_address);
	displacements[2] = MPI_Aint_diff(displacements[2], base_address);  
	
	MPI_Datatype types[3] = {MPI_INT,MPI_DOUBLE, MPI_CHAR};
	MPI_Type_create_struct(3, lenghts, displacements, types, &person_type);
	MPI_Type_commit(&person_type);

	// get my rank and do the corresponding job
	enum rank_roles {SENDER, RECEIVER};

	int my_rank;
	
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	switch(my_rank)
	{
		case SENDER:
			{		
				//send message
				struct person_t buffer;
				buffer.age = 45;
				buffer.height = 2.4;
				strncpy(buffer.name, "TOM", 9);
				buffer.name[9] = '\0';
				
				MPI_Send(&buffer,1,person_type, RECEIVER,0,MPI_COMM_WORLD);
				break;
			}
		case RECEIVER: 
			{
		// Receive the message 
		struct person_t received;

		MPI_Recv(&received, 1, person_type, SENDER, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			
		std::cout<< " age " << received.age << " height " << received.height << " Name " << received.name<<std::endl;
		break;}
	}

	MPI_Finalize();
	return 0; 

}
