// FILE: Statistician.h
// CLASS PROVIDED: statistician
//
// CONSTRUCTORS for statistician class:
//  statistician();
//   Postcondition: set values for stat_legth and stat_sum at 0.
//
// MODIFICATION MEMBER FUNCTIONS for the statistician class:
//  void next_number(double num)
//   Postcondition: the values for length, last, smallest, and largest have
//   been possibly altered depending on the new value recieved.
//
//  void erase()
//   Postcondition: sets the int stat_length and double stat_ sum to 0.
//
// CONSTANT MEMBER FUNCTIONS for the statistician class:
//  int length()
//   Postcondition: the value returned is the length of the sequence.
//
//  double last()
//   Precondition: assert stat_length > 0
//   Postcondition: the value returned is the last number in the sequence.
//
//  double sum()
//   Precondition: assert stat_length > 0
//   Postcondition: the value returned is the sum of the numbers in the sequence.
//
//  double mean()
//   Precondition: assert stat_length > 0
//   Postcondition: the value returned is the mean of the sequence.
//
//  double smallest()
//   Precondition: assert stat_length > 0
//   Postcondition: the value returned is the smallest number in the sequence.
//
//  double largest()
//   Precondition: assert stat_length > 0
//   Postcondition: the value returned is the largest number in the sequence.
//
//

#ifndef STATISTICIAN_H
#define STATISTICIAN_H

class statistician
{
public:
        void next_number(double num);
        int length();
        double last();
        double sum();
        double mean();
        double smallest();
        double largest();
        void erase();
        // CONSTRUCTOR
        statistician();
private:
        // PRIVATE MEMBER VARIABLES
        // keep track of certain details such as smallest,largest values,etc.
        double stat_smallest;
        double stat_largest;
        double stat_last;
        int stat_length;
        double stat_sum;
};

#endif
                                                                    