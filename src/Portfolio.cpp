#include <iostream>
#include <vector>
#include "Option.hpp"
#include "Portfolio.hpp"

using namespace std;

void Portfolio::addOptions(Option newOption)
{
    options.push_back(newOption);
}

void Portfolio::addOptions(vector<Option> newOptions)
{
    options.insert(options.end(), std::begin(newOptions), std::end(newOptions));
}

void Portfolio::removeAllOptions()
{
    options.clear();
}

vector<Option> Portfolio::getAllOptions() const
{
    return options;
}

bool Portfolio::validatePurchase(vector<Option> newOptions){
    // TODO: create the desired functionality according to the specification
    return false;
};