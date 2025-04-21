#ifndef brute_force_h
#define brute_force_h
#include <vector>
#include <utility>

// Función distancia del enunciado
double calculateDistance(std::pair<double, double> p1, std::pair<double, double>);

// Función de distancia mínima entre N puntos, fuerza bruta O(n^2)
double bruteforceMinDist(std::vector<std::pair<double, double>>);

// Función ligeramente mejor a BruteForce
double bruteforceMinDist_upgraded(std::vector<std::pair<double, double>>);

// Función mejor a BruteForce
double bruteforceMinDist_upgraded2(std::vector<std::pair<double, double>>);

// Función trivialemente lineal
double linear(std::vector<std::pair<double, double>>);

#endif
