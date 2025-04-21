#ifndef brute_force_h
#define brute_force_h
#include <vector>
#include <utility>

// Función distancia del enunciado
double calculateDistance(std::pair<double, double> p1, std::pair<double, double> p2);

// Función de distancia mínima entre N puntos, fuerza bruta O(n^2)
double bruteforceMinDist(std::vector<std::pair<double, double>> S);

// Primera version de bruteforce donde la embarré y ajusté prematuramente para que calculase menos de N(N-1) distancias :(
double bruteforceMinDist_oldest(std::vector<std::pair<double, double>> S);

// Función ligeramente mejor a BruteForce
double bruteforceMinDistBetter(std::vector<std::pair<double, double>> S);

#endif