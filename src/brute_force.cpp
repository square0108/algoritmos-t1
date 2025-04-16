#include <utility>
#include <set>
#include <limits>
#include <iostream>
#include <random>
#include "distance.h"

using namespace std;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> distr(-999,999);
const int N_POINTS = 3;

double bruteforceMinDist(set<pair<double,double>> S);

int main()
{
    set<pair<double,double>> test_lol;
    for (int i = 0; i < N_POINTS; i++) {
        pair<double,double> point = make_pair<double,double>((double) distr(gen),(double) distr(gen));
        test_lol.insert(point);
        cout << "(" << point.first << ", " << point.second << ") ";
    }
    cout << endl;
    cout << "mindist: " << bruteforceMinDist(test_lol) << endl;
    return 0;
}

double bruteforceMinDist(set<pair<double,double>> S)
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