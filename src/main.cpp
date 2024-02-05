#include "FileRW.hpp"
#include "Option.hpp"
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <VarianceCalculator.hpp>

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Options Portfolio Variance Tracker v.1.0" << endl;
    cout << "by Rafal K and Nhan N" << endl;
    cout << endl << endl << endl;

    int N = 30000;
    double r = 0.05;
    double sigma = 0.2;
    double S_0 = 5000.0;
    double t = 60.0;
    double limit = 10e8;

    vector<vector<double>> matrix;

    string filename = "sample_small.csv";
    string outputFileName = "variance_output.csv";

    std::ofstream outputFile(outputFileName);

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0) {
            filename = argv[i + 1];
        }
        if (strcmp(argv[i], "-n") == 0) {
            N = stoi(argv[i + 1]);
        }
        if (strcmp(argv[i], "-r") == 0) {
            r = stod(argv[i + 1]);
        }
        if (strcmp(argv[i], "-s") == 0) {
            sigma = stod(argv[i + 1]);
        }
        if (strcmp(argv[i], "-s0") == 0) {
            S_0 = stod(argv[i + 1]);
        }
        if (strcmp(argv[i], "-t") == 0) {
            t = stod(argv[i + 1]);
        }
        if (strcmp(argv[i], "-vl") == 0 || strcmp(argv[i], "--variance-limit") == 0) {
            limit = stod(argv[i + 1]);
        }
    }

    double dt = t / 365.0;

    VarianceCalculator vc = VarianceCalculator(N, r, sigma, S_0, dt);

    cout << "Reading file " << filename << "..." << endl;
    ifstream file;
    string line;

    cout << "no." << " " << "mean" << " " << "variance" << " " << "standard_deviation" << endl;
    outputFile << "no" << "," << "mean" << "," << "variance" << "," << "standard_deviation" << endl;
    cout << 0 << " " << 0 << " " << 0 << " " << 0 << endl;
    outputFile << 0 << "," << 0 << "," << 0 << "," << 0 << endl;


    file.open(filename);
    if (!file.is_open()) {
        cerr << "Could not open the file - '" << filename << "'" << std::endl;
        exit(EXIT_FAILURE);
    }

    int i = 1;

    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        if (line == "reset") {
            cout << "Resetting portfolio..." << endl;
            i = 0;
            vc.reset();
            continue;
        }
        
        Option newOption = FileRW::readOptionPurchase(line);

        vc.addNewOption(newOption);

        double mean = vc.getPortfolioMean();
        double varia = vc.estimateVariance();

        if (varia > limit) {
            cout << "Option (" << i << ") Exceeds variance limit!" << endl;
            cerr << "Variance exceeds limit! Exiting..." << endl;
            exit(EXIT_FAILURE);
        }

        cout << i << " " << mean << " " << varia << " " << sqrt(varia) << endl;
        outputFile << i << "," << mean << "," << varia << "," << sqrt(varia) << endl;
        i++;
    }

    file.close();
    outputFile.close();

    return 0;
}