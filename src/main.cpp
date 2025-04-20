#include "divide_and_conquer.h"
#include "brute_force.h"
#include "testing_functions.h"
#include <iostream>

int main()
{
    std::cout << "Inicio el test" << std::endl;

    test_complexity(bruteforceMinDist, "test3.csv", "brute_force", 8, 512, 1, 100);
    test_complexity(divideconquerMinDist, "test3.csv", "divide_n_conquer", 8, 512, 1, 100);

    std::cout << "Finalizo el test" << std::endl;

    return 0;
}
