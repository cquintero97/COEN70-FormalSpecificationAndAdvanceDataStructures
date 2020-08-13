// FILE: random.cpp
// Class IMPLEMENTED: RandGen (See random.h for documentation.)

#include "random.h"

RandGen::RandGen(int seed, int multiplier, int increment, int modulus)
{
        //Constructor sets the values for given variables
        rand_seed=(multiplier*seed+increment)%modulus;
        rand_multiplier=multiplier;
        rand_increment=increment;
        rand_modulus=modulus;
}

int RandGen::next()
{
        // calculates new seed and returns
        rand_seed=(rand_multiplier*rand_seed+rand_increment)%rand_modulus;
        return rand_seed;
}

void RandGen::setSeed(int seed)
{
        rand_seed=seed;
}
