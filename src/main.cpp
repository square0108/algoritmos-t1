#include "divide_and_conquer.h"
#include "brute_force.h"
#include "testing_functions.h"
#include <iostream>

const std::vector<int> two_powers = {8, 16, 32, 64, 128, 256, 512};

int main()
{
    std::cout << "Inició el test" << std::endl;

    // Todos contra todos
   //test_time(bruteforceMinDist, "all.csv", "Fuerza bruta", 8, 512, 1, 20);
   //test_time(bruteforceMinDist_upgraded, "all.csv", "Fuerza bruta con mejora trivial", 8, 512, 1, 20);
   //test_time(divideconquerMinDist, "all.csv", "Dividir y conquistar", 8, 512, 1, 20);

   //// Brute force
   //test_time(bruteforceMinDist, "BFvsBFUP.csv", "Fuerza bruta", 8, 512, 1, 20);
   //test_time(bruteforceMinDist_upgraded, "BFvsBFUP.csv", "Fuerza bruta con mejora trivial", 8, 512, 1, 20);
   //test_time(bruteforceMinDist_upgraded2, "BFvsBFUP.csv", "Fuerza bruta con mejora", 8, 512, 1, 20);

   //// Divide and conquer
   //test_time(divideconquerMinDist, "DaCvsDaCUP.csv", "Dividir y conquistar", 8, 512, 1, 20);

    // Test con potencias de 2
    //for (size_t i = 0; i < two_powers.size(); ++i)
    //{
    //    test_time(bruteforceMinDist, "test2power.csv", "Fuerza bruta (potencias de 2)", two_powers[i], two_powers[i], 1, 20);
    //    test_time(divideconquerMinDist, "test2power.csv", "Dividir y conquistar (potencias de 2)", two_powers[i], two_powers[i], 1, 20);
    //}

    // EJECUTAR DESPUES PERO CON DC_CASE_BASE = 4
    test_time(divideconquerMinDist, "all.csv", "Dividir y conquistar con mejora trivial", 8, 512, 1, 20);
    test_time(divideconquerMinDist, "DaCvsDaCUP.csv", "Dividir y conquistar con mejora trivial", 8, 512, 1, 20);

    std::cout << "Finalizó el test" << std::endl;

    return 0;
}
