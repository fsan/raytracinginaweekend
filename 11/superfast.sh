clang++ --std=c++14 main.cpp -o main -fopenmp -O3 -DQUALITY=0.5 -DBOUNCES=10 -DFACTOR=2 && time (./main > out.ppm) && display out.ppm  
