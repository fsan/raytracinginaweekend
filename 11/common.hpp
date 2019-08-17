#pragma once

#include <random>

/*
/ needed to change drand48 to something more robust because multithreading
/ for main sampling loop
/ it was getting in the way. if drand48 is kept we need just many more samples
/ i needed 8 times more samples with drand48 to get similar results than rand()
/ drand48 is twice as fast as rand, but then it started taking 4 times more
/ probably i should get a better number pseudo-random generator anyway. 
/
/ But letting it be called from material made it loooot worse, since it totally depends on it
/ It allowed to have much less samples and bouncing, but time was still greater (6x>) 
*/
inline double fRand()
{
        return (double)rand() / RAND_MAX;
}

inline double fRand_fast() {
    return drand48();
}
