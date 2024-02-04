#include "FileRW.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <Option.hpp>
#include <option_type.hpp>
#include <contract_type.hpp>

using namespace std;

Option FileRW::readOptionPurchase(string line) {
    istringstream ss(line);
    string token;
    vector<string> tokens;

    while (getline(ss, token, ',')) {
        tokens.push_back(token);
    }

    if (tokens.size() == 5) {
        option_type type = tokens[0][0] == 'C' ? call : put;
        contract_type position = tokens[1][0] == 'L' ? longPosition : shortPosition;
        double strikePrice = stod(tokens[2]);
        double timeToExpiry = stod(tokens[3]);
        int tradeVolume = stoi(tokens[4]);

        return Option(strikePrice, type, position, timeToExpiry, tradeVolume);
    }
}