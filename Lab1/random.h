// FILE: random.h
// CLASS PROVIDED: RandGen
//
// CONSTRUCTOR for the RandGen class:
//  RandGen(int seed, int multiplier, int increment, int modulus)
//   Postcondition: the values for rand_seed, rand_multiplier, rand_increment,
//   and rand_modulus have been set with the received values accordingly.
//
// MODIFICATION MEMBER FUNCTIONS for the RandGen class:
//  void setSeed(int num)
//   Postcondition: rand_seed is set as int num received
//
// CONSTANT MEMBER FUNCTIONS for the RandGen class:
//  int next()
//   Postcondition: returns rand_seed
//

#ifndef RANDGEN_H
#define RANDGEN_H

class RandGen
{
public:
        // CONSTRUCTOR
        RandGen(int seed, int multiplier, int increment, int modulus);
        // CONSTANT MEMBER FUNCTION
        int next();
        // MODIFICATION MEMBER FUNCTION
        void setSeed(int num);
private:
        int rand_seed;
        int rand_multiplier;
        int rand_increment;
        int rand_modulus;
};

#endif
