#ifndef OPTION_HPP
#define OPTION_HPP

#include <cmath>
#include "option_type.hpp"
#include "contract_type.hpp"

class Option
{
private:
    double strike_price;     // In multiples of 100, from 100 to 10 000.
    option_type type;        // Call or Put.
    contract_type contract;  // Long or Short.
    double time_to_maturity; // Time to maturity in days.
    int trade_volume;        // Trade volume in units of options.
public:
    Option(double strike, option_type option_type, contract_type contract_type, double ttm, int volume);
    double getStrikePrice();
    option_type getOptionType() const;
    contract_type getContractType() const;
    double getTimeToMaturity() const;
    int getTradeVolume() const;
    double getPayoff(double underlying) const;
};

#endif OPTION_HPP