#include <cmath>
#include "Option.hpp"
#include "option_type.hpp"
#include "contract_type.hpp"
#include "external/normdist.hpp"
#include <math.h>

#include <iostream>

using namespace std;

Option::Option(double strike, option_type option_type, contract_type contract_type, double ttm, int volume)
{
    strike_price = strike;
    type = option_type;
    contract = contract_type;
    time_to_maturity = ttm;
    trade_volume = volume;
}

double Option::getStrikePrice()
{
    return strike_price;
}

option_type Option::getOptionType() const
{
    return type;
}

contract_type Option::getContractType() const
{
    return contract;
}

double Option::getTimeToMaturity() const
{
    return time_to_maturity;
}

int Option::getTradeVolume() const
{
    return trade_volume;
}

double Option::getPayoff(double underlying) const {
    if (contract == longPosition) {
        if (type == call) return max(underlying - strike_price, 0.0) * trade_volume;
        if (type == put) return max(strike_price - underlying, 0.0) * trade_volume;
    }
    else if (contract == shortPosition) {
        if (type == call) return -max(underlying - strike_price, 0.0) * trade_volume;
        if (type == put) return -max(strike_price - underlying, 0.0) * trade_volume;
    }
}

double Option::getPrice(double S, double r, double sigma)
{
    double d1 = (log(S / strike_price) + (r + sigma * sigma * 0.5) * time_to_maturity) / sigma * sqrt(time_to_maturity);
    double d2 = d1 - sigma * sqrt(time_to_maturity);

    if (type == call)
        return N(d1) * S - N(d2) * strike_price * exp(-r * time_to_maturity);
    else
        return strike_price * exp(-r * time_to_maturity) * N(-d2) - S * N(-d1);
}