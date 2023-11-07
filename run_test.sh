# this script won't work
time ./no_thread -n 10000000000 >> result.txt

time ./naive_thread -t 1 -n 10000000000 >> result.txt
time ./naive_thread -t 2 -n 10000000000 >> result.txt
time ./naive_thread -t 3 -n 10000000000 >> result.txt
time ./naive_thread -t 4 -n 10000000000 >> result.txt
time ./naive_thread -t 5 -n 10000000000 >> result.txt
time ./naive_thread -t 6 -n 10000000000 >> result.txt
time ./naive_thread -t 7 -n 10000000000 >> result.txt
time ./naive_thread -t 8 -n 10000000000 >> result.txt
time ./naive_thread -t 9 -n 10000000000 >> result.txt
time ./naive_thread -t 10 -n 10000000000 >> result.txt
time ./naive_thread -t 11 -n 10000000000 >> result.txt
time ./naive_thread -t 12 -n 10000000000 >> result.txt
time ./naive_thread -t 13 -n 10000000000 >> result.txt
time ./naive_thread -t 14 -n 10000000000 >> result.txt
time ./naive_thread -t 15 -n 10000000000 >> result.txt
time ./naive_thread -t 16 -n 10000000000 >> result.txt

time ./openmp -t 1 -n 10000000000 >> result.txt
time ./openmp -t 2 -n 10000000000 >> result.txt
time ./openmp -t 3 -n 10000000000 >> result.txt
time ./openmp -t 4 -n 10000000000 >> result.txt
time ./openmp -t 5 -n 10000000000 >> result.txt
time ./openmp -t 6 -n 10000000000 >> result.txt
time ./openmp -t 7 -n 10000000000 >> result.txt
time ./openmp -t 8 -n 10000000000 >> result.txt
time ./openmp -t 9 -n 10000000000 >> result.txt
time ./openmp -t 10 -n 10000000000 >> result.txt
time ./openmp -t 11 -n 10000000000 >> result.txt
time ./openmp -t 12 -n 10000000000 >> result.txt
time ./openmp -t 13 -n 10000000000 >> result.txt
time ./openmp -t 14 -n 10000000000 >> result.txt
time ./openmp -t 15 -n 10000000000 >> result.txt
time ./openmp -t 16 -n 10000000000 >> result.txt