#! /bin/bash 

mkdir result

rm result/result.csv 
rm result/resultNon.csv

touch result/result.csv
touch result/resultNon.csv

chmod +x result/result.csv
chmod +x result/resultNon.csv

g++ creat_result_file.cpp -o file

./file

mpic++  blocking_ring_performance.cpp -o block
mpic++ non_blocking_ring.cpp -o non_block

for i in {2..8}

do
	mpirun -np $i ./block
	mpirun -np $i ./non_block
done 

exit
