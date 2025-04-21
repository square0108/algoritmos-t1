#ifndef divide_and_conquer_h
#define divide_and_conquer_h
#include <vector>
#include <utility>

double divideconquerMinDist(std::vector<std::pair<double, double>> points);

void debug_print_points(std::vector<std::pair<double, double>>);

bool compare_x(std::pair<double, double> p1, std::pair<double, double> p2);
#endif
