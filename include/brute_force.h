#ifndef brute_force_h
#define brute_force_h
#include <vector>
#include <utility>

// Función distancia del enunciado
double calculateDistance(std::pair<double,double> p1, std::pair<double,double> p2);

// Función de distancia mínima entre N puntos, fuerza bruta O(n^2)
double bruteforceMinDist(std::vector<std::pair<double,double>> S);

#endif