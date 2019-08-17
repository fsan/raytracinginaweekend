clang++ --std=c++14 main.cpp -o main -fopenmp -O3 -DQUALITY=4 -DBOUNCES=20 -DFACTOR=2 && time (./main > out.ppm) && display out.ppm  
