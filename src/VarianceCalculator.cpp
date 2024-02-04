#include "VarianceCalculator.hpp"
#include "FileRW.hpp"
#include "Option.hpp"
#include "external/inverse_cdf.hpp"
#include <vector>

using namespace std;

VarianceCalculator::VarianceCalculator(int N, double r, double sigma, double S_0, double dt) {
    vector<double> underlying = vector<double>(N);

    double dy = static_cast<double>(1) / (N + 1);

    for (int i = 0; i < N; i++) {
        double Z = inverseStandardNormal((i + 1) * dy);
        underlying[i] = S(r, sigma, dt, Z, S_0);
    }

    matrix.push_back(underlying);
}

double VarianceCalculator::S(double r, double sigma, double T, double Z, double S_0) const
{
    return exp((log(S_0) + (r - 0.5 * sigma * sigma) * T) + Z * sigma * sqrt(T));
}

double VarianceCalculator::getPortfolioVariance(double mean) {
    double variance = 0;

    for (double payoff : portfolioPayoff) {
        variance += pow(payoff - mean, 2);
    }

    return variance / portfolioPayoff.size();
}

double VarianceCalculator::getPortfolioMean() {
    double sum = 0;

    for (double payoff : portfolioPayoff) {
        sum += payoff;
    }
    return sum / portfolioPayoff.size();
}

void VarianceCalculator::getPortfolioSum() {
    portfolioPayoff.clear();

    for (int i = 0; i < matrix[0].size(); i++) {
        double sum = 0;
        for (int j = 1; j < matrix.size(); j++) {
            sum += matrix[j][i];
        }
        portfolioPayoff.push_back(sum);
    }
}

void VarianceCalculator::addNewOption(Option newOption) {
    vector<double> result;

    for (double St : matrix[0]) {
        double payoff = newOption.getPayoff(St);
        result.push_back(payoff);
    }

    matrix.push_back(result);

    getPortfolioSum();
}

double VarianceCalculator::estimateVariance(string line) {
    double mean = getPortfolioMean();
    return getPortfolioVariance(mean);
}

void VarianceCalculator::reset() {
    matrix.resize(1);
    portfolioPayoff.clear();
}