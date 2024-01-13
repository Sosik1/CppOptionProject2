#include <iostream>
#include "Experiment.hpp"
#include "FileRW.hpp"
#include "Option.hpp"

using namespace std;

int main() {
    Experiment exp;
    Experiment exp2;

    for (int i = 0; i < 365; i++) {
        exp.observations[i] = 6.66;
        exp2.observations[i] = 7.77;
    }

    cout << "IO Test" << endl;

    std::vector<Experiment> myExperiments;

    myExperiments.push_back(exp);
    myExperiments.push_back(exp2);

    cout << "writing experiments..." << endl;

    const string filename = "io_test.bin";
    FileRW::writeExperiments(filename, myExperiments);

    cout << "reading experiments..." << endl;

    size_t numExperiments = myExperiments.size();
    vector<Experiment> loadedExperiments = FileRW::readExperiments(filename, numExperiments);

    cout << "read experiments" << endl;

    if (loadedExperiments[0].observations[33] != 6.66) {
        cerr << "The first experiment is not read correctly";
        return 1;
    }

    if (loadedExperiments[1].observations[33] != 7.77) {
        cerr << "The second experiment is not read correctly";
        return 1;
    }

    string csvfilename = "options.csv";

    cout << "Reading file " << csvfilename << "..." << endl;

    vector<Option> inputOptions = FileRW::readOptionPurchases(csvfilename);

    if (inputOptions[0].getOptionType() != 0) {
        cerr << "Option type is not read correctly";
        return 1;
    }

    if (inputOptions[1].getContractType() != 1) {
        cerr << "Option position is not read correctly";
        return 1;
    }

    if (inputOptions[3].getStrikePrice() != 5400.0) {
        cerr << "Option position is not read correctly";
        return 1;
    }

    cout << "done :) files read and write correctly" << endl;

    cout << "starting load test..." << endl;

    vector<Experiment> loadTestVector;

    for (int i = 0; i < 10000; i++) {
        Experiment newExp{};
        for (int j = 0; j < 365; j++) {
            newExp.observations[j] = 4.44;
        }
        loadTestVector.push_back(newExp);
    }

    const string filename2 = "io_load_test.bin";
    FileRW::writeExperiments(filename2, loadTestVector);

    size_t numExperiments2 = loadTestVector.size();
    vector<Experiment> loadedExperiments2 = FileRW::readExperiments(filename2, numExperiments2);

    if (loadedExperiments2.size() < 334 || loadedExperiments2[333].observations[33] != 4.44) {
        cerr << "The load test is not read correctly";
        return 1;
    }

    cout << "load test complete :)" << endl;

    return 0;
}