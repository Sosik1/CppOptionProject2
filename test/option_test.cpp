#include <iostream>
#include "Option.hpp"
#include "contract_type.hpp"
#include "option_type.hpp"

using namespace std;

int main() {

	Option testOption = Option(100, option_type::call, contract_type::longPosition, 365, 1);

	if (testOption.getStrikePrice() != 100.0) return -1;

	cout << "asahmed" << endl;

	return 0;
}