#include <iostream>
#include "FileRW.hpp"
#include "Option.hpp"

using namespace std;

int main() {

    string csvfilename = "sample_small.csv";

    ifstream file;
    string line;

    file.open(csvfilename);

    cout << "Reading file " << csvfilename << "..." << endl;

    getline(file, line);

    Option inputOption = FileRW::readOptionPurchase(line);

    if (inputOption.getOptionType() != 0) {
        cerr << "Option type is not read correctly";
        return 1;
    }

    if (inputOption.getContractType() != 0) {
        cerr << "Option position is not read correctly";
        return 1;
    }

    if (inputOption.getStrikePrice() != 5000.0) {
        cerr << "Option position is not read correctly";
        return 1;
    }

    if (inputOption.getPayoff(5050) != 250) {
        cerr << "Option payoff is not read correctly";
        return 1;
    }

    if (inputOption.getTimeToMaturity() != 60) {
        cerr << "Option time to maturity is not read correctly";
        return 1;
    }

    if (inputOption.getTradeVolume() != 5) {
        cerr << "Option trade volume is not read correctly";
        return 1;
    }

    cout << "done :) files read and write correctly" << endl;
    cout << "io test complete :)" << endl;

    return 0;
}