clang++ --std=c++14 main.cpp -o main -fopenmp -O3 -DQUALITY=2 -DBOUNCES=10 -DFACTOR=2 && time (./main > out.ppm) && display out.ppm  
