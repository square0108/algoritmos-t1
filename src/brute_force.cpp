#include <limits>
#include <iostream>
#include "brute_force.h"
#include <math.h>

using namespace std;

double calculateDistance(std::pair<double,double> p1, std::pair<double,double> p2)
{
    return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
}

double bruteforceMinDist(vector<pair<double,double>> S)
{
    double min_dist = numeric_limits<double>::infinity();
    // Iterar sobre conjunto y calcular N-1, N-2, N-3, ..., 1 distancias, total N(N-1)
    for (auto p1 = S.begin(); p1 != S.end(); p1++) {
        auto p2 = p1;
        p2++;
        while (p2 != S.end()) {
            double dist = calculateDistance(*p1, *p2);
            if (min_dist > dist) min_dist = dist;
            p2++;
        }
    }
    return min_dist;
}