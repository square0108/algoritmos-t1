#ifndef testing_functions_h
#define testing_functions_h
#include <vector>
#include <utility>
#include <string>

void test_time(double (*function)(std::vector<std::pair<double, double>>), std::string filename, std::string testname, int min, int max, int step, int iterations);

void test_correctness(double (*function)(std::vector<std::pair<double, double>>), int, int, int);

#endif
