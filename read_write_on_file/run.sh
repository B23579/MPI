#! /bin/bash 

mkdir result

touch result/result.csv

chmod +x result/result.csv

g++ creat_result_file.cpp -o file

./file 
