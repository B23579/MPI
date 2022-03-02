#include<iostream>
#include<fstream>

int main(int arg, char **argv) {
	
	std::cout<<" My rank";

	std::ofstream result("result/result.csv");
	std::ofstream resultNon("result/resultNon.csv");
	
	if(result.is_open())
	{
		result<< "Size;Rank;walltime";
	}
	else{ std::cout<< "file not open";
		return 5;
		}
	result.close();	

	
	if(resultNon.is_open())
	{
		resultNon<< "Size;Rank;walltime";
	}
	else{ std::cout<< "file not open";
		return 5;
		}
	resultNon.close();	
	
	return 0; 

}
