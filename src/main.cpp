#include "divide_and_conquer.h"
#include "brute_force.h"
#include "testing_functions.h"
#include <iostream>

const std::vector<int> two_powers = {8,16,32,64,128,256,512};

int main()
{
    std::cout << "Inicio el test" << std::endl;

    // test_correctness(20, -20, 20);
    test_complexity(bruteforceMinDist, "test.csv", "brute_force", 8, 512, 1, 20);
    test_complexity(divideconquerMinDist, "test.csv", "divide_and_conquer", 8, 512, 1, 20);
    
    // Test con potencias de 2
    for (size_t i=0; i < two_powers.size(); ++i) {
        test_complexity(bruteforceMinDist, "test.csv", "brute_force_2pow", two_powers[i], two_powers[i], 1, 20);
        test_complexity(divideconquerMinDist, "test.csv", "divide_and_conquer_2pow", two_powers[i], two_powers[i], 1, 20);
    }

    std::cout << "Finalizo el test" << std::endl;

    return 0;
}
