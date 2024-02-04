#ifndef FILERW_HPP
#define FILERW_HPP

#include "Option.hpp"
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class FileRW {
public:
    static Option readOptionPurchase(string line);
};

#endif
