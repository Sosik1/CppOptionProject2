#include "Portfolio.hpp"
#include "Option.hpp"
#include "contract_type.hpp"
#include "option_type.hpp"

int main() {

	Portfolio testPortfolio;

	Option option = Option(100, option_type::call, contract_type::longPosition, 365, 1);

	return 0;
}