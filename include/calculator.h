#ifndef CALCULATOR_H
#define CALCULATOR_H

class Calculator {
public:
    Calculator();
    ~Calculator();
    
    // Add two integers
    int sum(int a, int b) const;
    
    // Calculate difference between two integers
    int difference(int a, int b) const;
};

#endif // CALCULATOR_H
