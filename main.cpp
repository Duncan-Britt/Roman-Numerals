#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <stdexcept>
#include "romanType.h"

int main() {
    // TEST CASES
    romanType num("MCXIV"); // 1114
    num.print();
    std::cout << num.getInt() << std::endl;
    
    romanType num2("CCCLIX"); // 359
    num2.print();
    std::cout << num2.getInt() << std::endl;

    romanType num3("MDCLXVI"); // 1666
    num3.print();
    std::cout << num3.getInt() << std::endl;
    
    romanType num4("CCCXL"); // 1666
    num4.print();
    std::cout << num4.getInt() << std::endl;

    romanType num5(949); // CMXLIX
    num5.print();
    std::cout << num5.getInt() << std::endl;

    std::cout << "MCXIV + CCCLIX = ";
    romanType sum = num + num2;
    sum.print();

    std::cout << "X / V = "; 
    (romanType(10) / romanType(5)).print().print().print();

    std::cout << num << std::endl;
}