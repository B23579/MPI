#include<iostream>
#include<fstream>

int main(int arg, char **argv) {
	
	std::cout<<" My rank";

	std::ofstream result("result/result.csv");
	
	if(result.is_open())
	{
		result<< "Size/Rank/walltime";
	}
	else{ std::cout<< "file not open";
		return 5;
		}
	result.close();	
	
	return 0; 

}
