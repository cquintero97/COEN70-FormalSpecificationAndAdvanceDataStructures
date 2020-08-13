// FILE: statistician.cpp
// CLASS IMPLEMENTED: statistician (See statistician.h for documentation.)

#include <cassert>              // Provides assert
#include <iostream>             // Allows c++ language
#include "statistician.h"       // Provides the statistician class definition
statistician::statistician()
{
        // Sets initial values for stat_length and stat_sum
        stat_length=0;
        stat_sum=0;
}

void statistician::next_number(double num)
{
        // function that adds recieved number to sum and check if the received
        // number should be set as the new smallest or largest number.
        stat_sum+=num;
        if (stat_length == 0)
        {
                stat_smallest = num;
                stat_largest = num;
        }
        else
        {
                if (num > stat_largest)
                {
                        stat_largest=num;
                }
                else if (num<stat_smallest)
                {
                        stat_smallest=num;
                }
        }
        stat_last=num;  //received number is set as last number in sequence
        stat_length++;
}

int statistician::length()
{
        return stat_length;
}

double statistician::last()
{
        assert(stat_length>0);
        return stat_last;
}

double statistician::sum()
{
        assert(stat_length>0);
        return stat_sum;
}

double statistician::mean()
{
        assert(stat_length>0);
        return stat_sum/stat_length;
}

double statistician::smallest()
{
        assert(stat_length>0);
        return stat_smallest;
}

double statistician::largest()
{
        assert(stat_length>0);
        return stat_largest;
}

void statistician::erase()
{
        stat_length = 0;
        stat_sum = 0.0;
}
