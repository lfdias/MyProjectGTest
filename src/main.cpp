#include <iostream>
#include "../include/my_math.h"

int main() {
    MyMath math; 
    int a = 3;
    int b = 4;
    std::cout << "Sum: " << math.add(a, b) << std::endl; 
    return 0;
}
