#ifndef PORTFOLIO_HPP
#define PORTFOLIO_HPP

#include <vector>
#include "Option.hpp"

using namespace std;

class Portfolio
{
private:
    std::vector<Option> options;

public:
    void addOptions(Option newOption);

    void addOptions(std::vector<Option> newOptions);

    void removeAllOptions();

    std::vector<Option> getAllOptions() const;

    bool validatePurchase(std::vector<Option> newOptions);
};

#endif PORTFOLIO_HPP