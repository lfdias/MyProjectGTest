#include "utilities.h"

bool isPair(int number) {
    // Um número é par se o último bit (bit menos significativo) for 0.
    return (number & 1) == 0;
}