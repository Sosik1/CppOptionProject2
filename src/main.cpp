#include "FileRW.hpp"
#include "Option.hpp"
#include "external/inverse_cdf.hpp"
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

double S(double r, double sigma, double T, double Z, double S_0)
{
    return exp((log(S_0) + (r - 0.5 * sigma * sigma) * T) + Z * sigma * sqrt(T));
}

double getPortfolioVariance(vector<double> portfolioPayoffs, double mean) {
    double variance = 0;

    for (double payoff : portfolioPayoffs) {
        variance += pow(payoff - mean, 2);
    }

    return variance / portfolioPayoffs.size();
}

double getPortfolioMean(vector<double> portfolioPayoffs) {
    double sum = 0;

    for (double payoff : portfolioPayoffs) {
        sum += payoff;
    }
    return sum / portfolioPayoffs.size();
}

vector<double> getPortfolioSum(vector<vector<double>> matrix) {
    vector<double> result;

    for (int i = 0; i < matrix[0].size(); i++) {
        double sum = 0;
        for (int j = 1; j < matrix.size(); j++) {
            sum += matrix[j][i];
        }
        result.push_back(sum);
    }

    return result;
}

void addNewOption(Option newOption, vector<vector<double>> &matrix) {
    vector<double> result;

    for (double St : matrix[0]) {
        double payoff = newOption.getPayoff(St);
        result.push_back(payoff);
    }

    matrix.push_back(result);
}

void initializeMatrix(vector<vector<double>> &matrix, int N, double r, double sigma, double S_0, double dt) {
    vector<double> underlying = vector<double>(N);

    double dy = static_cast<double>(1) / (N + 1);

    for (int i = 0; i < N; i++) {
        double Z = inverseStandardNormal((i + 1) * dy);
        underlying[i] = S(r, sigma, dt, Z, S_0);
    }

    matrix.push_back(underlying);
}

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

    initializeMatrix(matrix, N, r, sigma, S_0, dt);

    cout << "Reading file " << filename << "..." << endl;
    ifstream file;
    string line;

    cout << "no." << " " << "trades" << " " << "mean" << " " << "variance" << " " << "standard_deviation" << endl;
    cout << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << endl;

    file.open(filename);
    if (!file.is_open()) {
        cerr << "Could not open the file - '" << filename << "'" << std::endl;
        exit(EXIT_FAILURE);
    }

    int i = 1;

    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        
        Option newOption = FileRW::readOptionPurchase(line);

        addNewOption(newOption, matrix);

        vector<double> portfolioPayoff = getPortfolioSum(matrix);

        double mean = getPortfolioMean(portfolioPayoff);
        double varia = getPortfolioVariance(portfolioPayoff, mean);


        if (varia > limit) {
            cout << "Option (" << i << ") Exceeds variance limit!" << endl;
            cerr << "Variance exceeds limit! Exiting..." << endl;
            exit(EXIT_FAILURE);
        }

        cout << i << " " << mean << " " << varia << " " << sqrt(varia) << endl;
        i++;
    }

    return 0;
}