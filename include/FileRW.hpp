#ifndef FILERW_HPP
#define FILERW_HPP

#include "Experiment.hpp"
#include "Option.hpp"
#include <vector>

using namespace std;

class FileRW {
public:
    static void writeExperiments(const string& filename, const vector<Experiment>& experiments);
    static vector<Experiment> readExperiments(const string& filename, size_t numExperiments);
    static vector<Option> readOptionPurchases(const string& filename);
};

#endif
