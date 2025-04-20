#include "divide_and_conquer.h"
#include "brute_force.h"

#include <iostream>
#include <vector>
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

// Función que con un input (n largo array, valor minimo, valor máximo)
// genere un array de n puntos random (valores array son pair<double,double>)
// Quizas despues puede generar puntos según una distribución
vector<pair<double, double>> generatePoints(int n, int min, int max)
{
    std::default_random_engine generator;

    uniform_real_distribution<> dis(min, max); // Distribución uniforme en [min, max]

    vector<pair<double, double>> points;
    points.reserve(n);

    for (int i = 0; i < n; ++i)
    {
        double x = dis(generator);
        double y = dis(generator);
        points.emplace_back(x, y);
    }

    return points;
}

/*
 * Función para revisar la correctitud del algoritmo d&c con algunos casos patológicos.
 */
void test_correctness(int n, int min, int max)
{
    std::default_random_engine generator;
    uniform_real_distribution<> dis(min, max);
    

    for (int i = 0; i < 20; ++i) { 
        // Fijamos un x
        int fixed_x = dis(generator);

        vector<pair<double, double>> points;
        points.reserve(n);

        for (int i = 0; i < n; ++i) {
            double y = dis(generator);
            points.emplace_back(fixed_x, y);
        }

        std::cout << "Puntos: ";
        // debug_print_points(points);

        int bf_min = bruteforceMinDist(points);
        int dc_min = divideconquerMinDist(points);

        std::cout << "n=" << n << ", bf_min=" << bf_min << ", dc_min=" << dc_min << std::endl;
        if (dc_min != bf_min) {
            std::cout << "Failed" << std::endl;
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
