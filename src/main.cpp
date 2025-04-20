#include "divide_and_conquer.h"
#include "brute_force.h"
#include "testing_functions.h"
#include <iostream>

int main()
{
    std::cout << "Inicio el test" << std::endl;

    test_correctness(20, -20, 20);
    // test_complexity(bruteforceMinDist, "test.csv", "brute_force", 8, 512, 1, 20);
    // test_complexity(divideconquerMinDist, "test.csv", "divide_n_conquer", 8, 512, 1, 20);

    std::cout << "Finalizo el test" << std::endl;

    return 0;
}
