#include <iostream>
#include "../include/my_math.h"

int main() {
    MyMath math; // Instância da classe MyMath
    int a = 3;
    int b = 4;
    std::cout << "Sum: " << math.add(a, b) << std::endl; // Chamando o método add no objeto math
    return 0;
}
