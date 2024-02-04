#include <iostream>
#include "Option.hpp"
#include "contract_type.hpp"
#include "option_type.hpp"

using namespace std;

int main() {

	Option testOption = Option(100.0, option_type::call, contract_type::longPosition, 365, 1);

    if (testOption.getOptionType() != 0) {
        cerr << "Option type is not read correctly";
        return 1;
    }

    if (testOption.getContractType() != 0) {
        cerr << "Option position is not read correctly";
        return 1;
    }

    if (testOption.getStrikePrice() != 100.0) {
        cerr << "Option position is not read correctly";
        return 1;
    }

    if (testOption.getPayoff(200.0) != 100.0) {
        cerr << "Option payoff is not read correctly";
        return 1;
    }

    if (testOption.getTimeToMaturity() != 365.0) {
        cerr << "Option time to maturity is not read correctly";
        return 1;
    }

    if (testOption.getTradeVolume() != 1) {
        cerr << "Option trade volume is not read correctly";
        return 1;
    }

    cout << "option test passing successfully :)" << endl;

	return 0;
}