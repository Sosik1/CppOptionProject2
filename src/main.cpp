#include "Portfolio.hpp"
#include <iostream>
#include <Experiment.hpp>
#include <FileRW.hpp>
#include <Option.hpp>

using namespace std;

int main()
{

    cout << "Options Portfolio Variance Tracker v.1.0" << endl;

    Portfolio portfolio;

    string filename = "options.csv";

    cout << "Reading file " << filename << endl;

    vector<Option> inputOptions = FileRW::readOptionPurchases(filename);

    for (Option option : inputOptions) {
        cout << option.getContractType() << option.getOptionType() << option.getStrikePrice() << option.getTimeToMaturity() << option.getTradeVolume() << endl;
    }

    return 0;
}