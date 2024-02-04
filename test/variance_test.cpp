#include <iostream>
#include "Option.hpp"
#include "VarianceCalculator.hpp"
#include "contract_type.hpp"
#include "option_type.hpp"

using namespace std;

int main() {
    // Initialize parameters
    int N = 30000;
    double r = 0.05;
    double sigma = 0.2;
    double S_0 = 5000.0;
    double dt = 60.0 / 365.0;

    double test_tolerance = 0.001; // 0.1%

    double correctMean = 919.183127;
    double correctVariance = 1.743876e+06;

    Option newOption = Option(5000, call, longPosition, 60, 5);

    VarianceCalculator vc = VarianceCalculator(N, r, sigma, S_0, dt);

    vc.addNewOption(newOption);

    double mean = vc.getPortfolioMean();
    double varia = vc.estimateVariance();

    if (abs(correctMean - mean) > correctMean * test_tolerance) {
        cout << "Correct value: " << correctMean << " Received value: " << mean << endl;
        cerr << "The mean value exceeds tolerance of 0.1%" << endl;
        return 1;
    }

    if (abs(correctVariance - varia) > correctVariance * test_tolerance) {
        cout << "Correct value: " << correctVariance << " Received value: " << varia << endl;
        cerr << "The variance value exceeds tolerance of 0.1%" << endl;
        return 1;
    }

    Option newOption2 = Option(5500, call, shortPosition, 60, 5);
    Option newOption3 = Option(5000, put, shortPosition, 60, 5);
    Option newOption4 = Option(5500, put, longPosition, 60, 5);

    vc.addNewOption(newOption2);
    vc.addNewOption(newOption3);
    vc.addNewOption(newOption4);
    
    // Variance should be very close to 0
    double varia2 = vc.estimateVariance();

    cout << "Correct value: 0 " << " Received value: " << varia2 << endl;

    if (abs(0 - varia2) > test_tolerance) {
        cout << "Correct value: 0 " << " Received value: " << varia2 << endl;
        cerr << "The edge case variance value exceeds tolerance of 0.1%" << endl;
        return 1;
    }

    vc.reset();

    cout << "End-to-end tests passed :)" << endl;

    return 0;
}