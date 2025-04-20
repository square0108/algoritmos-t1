#include "divide_and_conquer.h"
#include "brute_force.h"
#include <limits>
#include <algorithm>
#include <random>
#include <set>
#include <math.h>
#include <iostream>

using namespace std;

// estos compare solo son para utilizar std::sort1
bool compare_x(std::pair<double, double> p1, std::pair<double, double> p2);
bool compare_y(std::pair<double, double> p1, std::pair<double, double> p2);

double _mindist(std::vector<std::pair<double, double>> P, std::vector<std::pair<double, double>> X, std::vector<std::pair<double, double>> Y);
void debug_print_points(std::vector<std::pair<double, double>> P);

// random number generator, probar modificando distribuciones
std::random_device rd;
std::mt19937 gen(rd());
std::geometric_distribution<> distr(0.013331);
const int N_POINTS = 11;
const bool DEBUG = 0;
/*
int main()
{
	std::vector<std::pair<double,double>> blangonga;
	// set de puntos bonitos :)
	// {make_pair(0,1),make_pair(1,0),make_pair(2,0.5),make_pair(2.2,1),make_pair(4.2,2),make_pair(4.2,1)};
	for (int i = 0; i < N_POINTS; ++i) {
		blangonga.push_back(std::make_pair<double,double>((double) distr(gen), (double) distr(gen)));
	}
	std::cout << "mindist DIVIDE AND CONQUER:\n " << divideconquerMinDist(blangonga) << std::endl;
	std::cout << "mindist BRUTEFORCE: " << bruteforceMinDist(blangonga) << std::endl;
	return 0;

*/

/* Esta NO ES la función que recursa (la indicada es _mindist), sólo hace el pre-sort. */
double divideconquerMinDist(std::vector<std::pair<double, double>> points)
{
	std::vector<std::pair<double, double>> X = points;
	std::vector<std::pair<double, double>> Y = points;
	std::sort(X.begin(), X.end(), compare_x);
	std::sort(Y.begin(), Y.end(), compare_y);

	return _mindist(points, X, Y);
}

/* Función basada en el algoritmo descrito por el libro Introduction to Algorithms en la sección 33.4 "Finding the closest pair of points"
	Tiempo de ejecución O(n lg n).

	Input: arreglo de puntos P, arreglos ordenados X, Y (puntos de P ordenados según valores de coordenadas X e Y respectivamente)
	Output: distancia mínima entre dos puntos de P
*/
double _mindist(std::vector<std::pair<double, double>> P, std::vector<std::pair<double, double>> X, std::vector<std::pair<double, double>> Y)
{
	// Caso base de la recursión
	if (P.size() <= 3)
		return bruteforceMinDist(P);

	/*
	P_L y P_R son subconjuntos de P tal que floor(|P|/2) = |P_L| y ceil(|P|/2) = |P_R|
	X_L y Y_L son subconjuntos ordenados de X e Y que están la izquierda de la recta de bisección (pertenecen a P_L)
	X_R y Y_R idem (pertenecen a P_R)
	*/
	std::vector<std::pair<double, double>> P_L, P_R, X_L, X_R, Y_L, Y_R;
	/* P.size() / 2 es equivalente a floor(|P|/2) */
	for (size_t i = 0; i < P.size() / 2; ++i)
	{
		P_L.push_back(X[i]);
		X_L.push_back(X[i]);
	}
	for (size_t i = (P.size() / 2); i < P.size(); ++i)
	{
		P_R.push_back(X[i]);
		X_R.push_back(X[i]);
	}

    auto mediana = X_R[0];


    /* 
     * Primero ingresamos a X_R los elementos que se encuentran a la derecha de la mediana, y a 
     * X_L los que se encuentran a la izquierda.
     */
	for (auto pair : Y) {
        if (pair.first > mediana.first) {
            Y_R.push_back(pair);
        } else if (pair.first == mediana.first && pair.second >= mediana.second) {
            Y_R.push_back(pair);
        } else {
            Y_L.push_back(pair);
        }
	}


    
	// debug debug
	if (DEBUG) {
        std::cout << "jeje" << std::endl;
		std::cout << "X: ";
		debug_print_points(X);
		std::cout << "Y: ";
		debug_print_points(Y);
		std::cout << "X_L: ";
		debug_print_points(X_L);
		std::cout << "X_R: ";
		debug_print_points(X_R);
		std::cout << "Y_L: ";
		debug_print_points(Y_L);
		std::cout << "Y_R: ";
		debug_print_points(Y_R);
	}

	// obtener mindist de P_L y P_R, y asignar a ``dist`` la menor de las dos
	double dist = 0;
	double d1 = _mindist(P_L, X_L, Y_L);
	double d2 = _mindist(P_R, X_R, Y_R);
	dist = (d1 > d2) ? d2 : d1;

	if (DEBUG)
		std::cout << "d1=" << d1 << ", d2=" << d2 << "delta=" << dist << std::endl;

	// filtrar sólo los puntos de P_L y P_R  con ``dist`` distancia respecto a la recta

	std::vector<std::pair<double,double>> strip;
	for (auto p : Y) {
        if (abs(mediana.first - p.first) < dist) strip.push_back(p);
		//if (abs(bisection_X - p.first) < dist)
	    //	strip.push_back(p);
	}

	// de de debug print
	//if (DEBUG)
	//{
	//	std::cout << "strip: ";
	//	debug_print_points(strip);
	//	std::cout << std::endl;
	//}

	for (size_t i = 0; i < strip.size(); ++i)
	{
		for (size_t j = i + 1; j < (i + 8 < strip.size() ? i + 8 : strip.size()); ++j)
		{
			if (calculateDistance(strip[i], strip[j]) < dist)
				dist = calculateDistance(strip[i], strip[j]);
		}
	}

	return dist;
}

/* Retorna True si p1 < p2 orden lexicografico x-y*/
bool compare_x(std::pair<double, double> p1, std::pair<double, double> p2)
{
    if (p1.first < p2.first) {
        return true;
    } else if (p1.first == p2.first) {
        return p1.second < p2.second;
    } else {
        return false;
    }
}

/* Retorna True si p1 < p2 orden lexicografico y-x*/
bool compare_y(std::pair<double, double> p1, std::pair<double, double> p2)
{
    if (p1.second < p2.second) {
        return true;
    } else if (p1.second == p2.second) {
        return p1.first < p2.first;
    } else {
        return false;
    }
}

void debug_print_points(std::vector<std::pair<double, double>> P)
{
	std::cout << "Points set: ";
	for (auto p : P)
	{
		std::cout << "(" << p.first << "," << p.second << ") ";
	}
	std::cout << std::endl;
}
