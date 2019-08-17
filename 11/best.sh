clang++ --std=c++14 main.cpp -o main -fopenmp -O3 -DQUALITY=9 -DBOUNCES=90 -DFACTOR=4 && time (./main > out.ppm) && display out.ppm  
