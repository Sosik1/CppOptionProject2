#include "FileRW.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <Option.hpp>
#include <option_type.hpp>
#include <contract_type.hpp>

using namespace std;

void FileRW::writeExperiments(const string& filename, const vector<Experiment>& experiments) {
    ofstream outFile(filename, ios::binary);

    if (!outFile) {
        cerr << "Error opening file for writing" << endl;
        return;
    }

    for (const auto& exp : experiments) {
        exp.serialize(outFile);
    }
}

vector<Experiment> FileRW::readExperiments(const string& filename, size_t numExperiments) {
    vector<Experiment> experiments(numExperiments);
    ifstream inFile(filename, ios::binary);

    if (!inFile) {
        cerr << "Error opening file for reading" << endl;
        return experiments;
    }

    for (auto& exp : experiments) {
        exp.deserialize(inFile);
    }

    return experiments;
}

vector<Option> FileRW::readOptionPurchases(const string& filename) {
    vector<Option> purchases;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

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

            purchases.emplace_back(strikePrice, type, position, timeToExpiry, tradeVolume);

        }
    }
    return purchases;
}