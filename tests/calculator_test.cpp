#include <iostream>
#include <cassert>
#include "calculator.h"

void test_sum() {
    Calculator calc;
    
    // Test positive numbers
    assert(calc.sum(5, 3) == 8);
    assert(calc.sum(10, 20) == 30);
    
    // Test negative numbers
    assert(calc.sum(-5, 3) == -2);
    assert(calc.sum(-5, -3) == -8);
    
    // Test zero
    assert(calc.sum(0, 0) == 0);
    assert(calc.sum(5, 0) == 5);
    
    std::cout << "✓ test_sum PASSED\n";
}

void test_difference() {
    Calculator calc;
    
    // Test positive numbers
    assert(calc.difference(10, 3) == 7);
    assert(calc.difference(20, 5) == 15);
    
    // Test negative numbers
    assert(calc.difference(-10, 3) == -13);
    assert(calc.difference(3, -5) == 8);
    
    // Test zero
    assert(calc.difference(0, 0) == 0);
    assert(calc.difference(5, 0) == 5);
    assert(calc.difference(0, 5) == -5);
    
    std::cout << "✓ test_difference PASSED\n";
}

int main() {
    std::cout << "\n=== Running Calculator Tests ===\n\n";
    
    try {
        test_sum();
        test_difference();
        
        std::cout << "\n=== All Tests PASSED ===\n\n";
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }
}
