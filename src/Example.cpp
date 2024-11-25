#include "Example.hpp"


// Calculates the square of a number between -10 and 10 
int square(int number)
{
    if (number > 10 || number < -10) 
    {
        return 99999;  // Return 99999 for invalid values
    }
    return number * number;

}