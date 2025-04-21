#include "divide_and_conquer.h"
#include "brute_force.h"

#include <iostream>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <fstream>

using namespace std;

// Función que con un input (array de puntos, función de minimo) return tiemo que demoro en nanosegundos (chrono)
// quizas guardar como int64_t
int64_t getTime(vector<pair<double, double>> points, double (*function)(vector<pair<double, double>>))
{
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point end_time;

    start_time = std::chrono::high_resolution_clock::now();

    function(points);

    end_time = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);

    return duration.count();
}

/*Función que con un input (n largo array, valor minimo, valor máximo)
 genere un array de n puntos random (valores array son pair<double,double>)*/
vector<pair<double, double>> generatePoints(int n, int min, int max)
{
    std::default_random_engine generator;

    uniform_real_distribution<> dis(min, max); // Distribución uniforme en [min, max]

    set<pair<double, double>> point_set;

    while (point_set.size() < n) {
        
        double x = dis(generator);
        double y = dis(generator);
        point_set.emplace(x, y);
    }
    

    vector<pair<double, double>> points;
    points.reserve(n);
    points.assign(point_set.begin(), point_set.end());

    return points;
}

/*
 * Función para revisar la correctitud del algoritmo d&c con algunos casos patológicos.
 - n: cantidad de elementos en los vectores
 */
void test_correctness(int n, int min, int max)
{

    vector<vector<pair<double, double>>> test_cases;

    vector<pair<double, double>> puntos_lindos = {make_pair(1, 4), make_pair(-1, 0), make_pair(3, 4), make_pair(7, 8), make_pair(6, -2), make_pair(3, 2), make_pair(-2, 0), make_pair(3, 7)};

    vector<pair<double, double>> singleton = {make_pair(1, 4)};

    vector<pair<double, double>> par = {make_pair(1, 4), make_pair(5, 7)};

    test_cases.push_back(puntos_lindos);
    test_cases.push_back(singleton);
    test_cases.push_back(par);


    /* Puntos aleatorios */
    for (int i = 0; i < 20; ++i)
    {
        vector<pair<double, double>> points = generatePoints(n, min, max);

        test_cases.push_back(points);
    }

    std::default_random_engine generator;
    uniform_real_distribution<> dis(min, max);

    /* Puntos con misma coordenada x */
    for (int i = 0; i < 20; ++i)
    {
        // Fijamos un x
        double fixed_x = dis(generator);

        set<pair<double, double>> point_set;

        while (point_set.size() < n) {
            double y = dis(generator);
            point_set.emplace(fixed_x, y);
        }
        
        vector<pair<double, double>> points;
        points.assign(point_set.begin(), point_set.end());

        test_cases.push_back(points);

    }

    /* Puntos con misma coordenada y */
    for (int i = 0; i < 20; ++i)
    {
        // Fijamos un x
        double fixed_y = dis(generator);

        set<pair<double, double>> point_set;

        while (point_set.size() < n) {
            double x = dis(generator);
            point_set.emplace(x, fixed_y);
        }
        
        vector<pair<double, double>> points;
        points.assign(point_set.begin(), point_set.end());

        test_cases.push_back(points);
    }

    /* Puntos con coordenadas formando una cruz (borde de orden lexicografico)*/
    for (int i = 0; i < 20; ++i)
    {

        set<pair<double, double>> point_set;

        double x = dis(generator);
        double y = dis(generator);

        while (point_set.size() < n) {

            if (dis(generator) >= (max + min) / 2) {
                point_set.emplace(dis(generator), y);
            } else {
                point_set.emplace(x, dis(generator));
            }
        }


        vector<pair<double, double>> points;
        points.assign(point_set.begin(), point_set.end());


        test_cases.push_back(points);
    }

    for (auto points : test_cases)
    {

        std::cout << "Puntos: ";
        debug_print_points(points);
        double bf_min = bruteforceMinDist(points);
        double dc_min = divideconquerMinDist(points);

        std::cout << "bf_min=" << bf_min << ", dc_min=" << dc_min << ", bf_m_min=" << bf_m_min << std::endl;
        if (dc_min != bf_min || bf_m_min != bf_min)
        {
            std::cout << "Failed" << std::endl;
            break;
        }
    }
}

/*
Función para testear complejidad temporal de forma experimental, donde:
- function: función a evaluar, en este caso destinada a encontrar la distancia minima entre dos puntos,
en un set de puntos.
- filename: Archivo donde se guardaran los datos
- testname: nombre del test.
- min: Cantidad minima de puntos
- max: Cantidad maxima de puntos
- step: Salto de un test a otro
- iterations: Cantidad de iteraciones por cada cantidad de puntos.
*/
void test_complexity(double (*function)(vector<pair<double, double>>), string filename, string testname, int min, int max, int step, int iterations)
{
    string filepath = "tests/" + filename;

    // modo appen
    ofstream file(filepath, ios::app);

    if (!file.is_open())
    {
        cerr << "Error al abrir archivo " << filepath << endl;
        return;
    }

    // vemos si tiene datos (check primera fila)
    ifstream checkFile(filepath);
    checkFile.seekg(0, ios::end);
    if (checkFile.tellg() == 0)
    {
        file << "test_name,n,time_ns\n";
    }
    checkFile.close();

    for (int i = min; i <= max; i += step)
    {
        for (int j = 0; j < iterations; ++j)
        {
            auto points = generatePoints(i, 0, 100);
            int64_t time = getTime(points, function);

            file << testname << "," << i << "," << time << "\n";
        }
    }

    file.close();

    cout << "Archivo guardado en " << filepath << endl;
}
