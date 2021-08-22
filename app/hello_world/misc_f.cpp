#include <iostream>
#include <string>
#include "misc_f.hpp"
#include <stdlib.h>

static int add_f()
{
    // prompt user to enter two numbers
    std::cout << "Enter two numbers:" << std::endl; 

    int v1, v2;
    std::cin >> v1 >> v2;   

    std::cout << "The sum of " << v1 << " and " << v2
              << " is " << v1 + v2 << std::endl;

    return 0;
}


void misc_fun_cpp_test()
{
    add_f();


    exit(0);
}


