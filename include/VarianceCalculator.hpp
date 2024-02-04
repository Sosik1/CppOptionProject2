#ifndef VARIANCE_CALCULATOR_HPP
#define VARIANCE_CALCULATOR_HPP

#include <cmath>
#include "option_type.hpp"
#include "contract_type.hpp"
#include "Option.hpp"
#include <vector>
#include <string>

using namespace std;

class VarianceCalculator
{
private:
	vector<vector<double>> matrix;
	vector<double> portfolioPayoff;
	double S(double r, double sigma, double T, double Z, double S_0) const;
	double getPortfolioVariance(double mean);
	void getPortfolioSum();
public:
	double estimateVariance(string line);
	void addNewOption(Option newOption);
	double getPortfolioMean();
	VarianceCalculator(int N, double r, double sigma, double S_0, double dt);
	void reset();
};

#endif VARIANCE_CALCULATOR_HPP