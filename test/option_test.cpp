#include <iostream>
#include "Option.hpp"
#include "contract_type.hpp"
#include "option_type.hpp"

using namespace std;

int main() {

	Option testOption = Option(100, option_type::call, contract_type::longPosition, 365, 1);

	if (testOption.getStrikePrice() != 100.0) {
		cerr << "The strike price is not stored correctly" << endl;
		return -1;
	}




	return 0;
}