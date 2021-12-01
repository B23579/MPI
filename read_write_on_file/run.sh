#! /bin/bash 

mkdir result

touch result/result.csv

chmod +x result/result.csv

g++ creat_result_file.cpp -o file

./file

mpicxx  blocking_ring_performance.cpp -o block

for i in {2..8}

do
	mpirun -np $i block
done 

 
