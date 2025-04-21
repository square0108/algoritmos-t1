#include <limits>
#include <iostream>
#include "brute_force.h"
#include "divide_and_conquer.h"
#include <math.h>
#include <algorithm>

using namespace std;

double calculateDistance(std::pair<double, double> p1, std::pair<double, double> p2)
{
    return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
}

// Iterar sobre conjunto de puntos y calcular N(N-1) distancias, N-1 por cada punto
double bruteforceMinDist(vector<pair<double, double>> S)
{
    double min_dist = numeric_limits<double>::infinity();
    for (auto p1 = S.begin(); p1 != S.end(); p1++)
    {
        for (auto p2 = S.begin(); p2 != S.end() && (*p1) != (*p2); p2++)
        {
            double dist = calculateDistance(*p1, *p2);
            if ((min_dist) > dist)
                min_dist = dist;
        }
    }
    return min_dist;
}

// Iterar sobre conjunto y calcular N-1, N-2, N-3, ..., 1 distancias, levemente mejor que la anterior
double bruteforceMinDist_upgraded(vector<pair<double, double>> S)
{
    double min_dist = numeric_limits<double>::infinity();
    for (auto p1 = S.begin(); p1 != S.end(); p1++)
    {
        auto p2 = p1;
        p2++;
        while (p2 != S.end())
        {
            double dist = calculateDistance(*p1, *p2);
            if (min_dist > dist)
                min_dist = dist;
            p2++;
        }
    }
    return min_dist;
}

// Ordenar con con respecto al eje x de  forma creciente
// Iterar sobre conjunto y calcular N-1, N-2, N-3, ..., 1 distancias
// Parar si x_{i+1} - x_{i} > distacia mínima
double bruteforceMinDist_upgraded2(vector<pair<double, double>> S)
{
    double min_dist = numeric_limits<double>::infinity();

    // Ordenamos con respecto a x
    std::sort(S.begin(), S.end(), compare_x);

    // Iterar sobre conjunto y calcular N-1, N-2, N-3, ..., 1 distancias, total N(N-1)
    for (auto p1 = S.begin(); p1 != S.end(); p1++)
    {
        auto p2 = p1;
        p2++;
        while (p2 != S.end())
        {
            double dist = calculateDistance(*p1, *p2);
            if (min_dist > dist)
                min_dist = dist;

            // Si la distancia entre x_{i} y x_{i+1} es mayor a la distancia minima encontrada, entonces
            // no vale la pena seguir comparando
            if ((*p2).first - (*p1).first > min_dist)
            {
                break;
            }

            p2++;
        }
    }
    return min_dist;
}