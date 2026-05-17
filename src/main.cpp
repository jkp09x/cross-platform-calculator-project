#include <iostream>
#include "calculator.h"

int main() {
    Calculator calc;
    
    int a = 10;
    int b = 5;
    
    std::cout << "Calculator Demo\n";
    std::cout << "===============\n";
    std::cout << a << " + " << b << " = " << calc.sum(a, b) << std::endl;
    std::cout << a << " - " << b << " = " << calc.difference(a, b) << std::endl;
    
    return 0;
}
