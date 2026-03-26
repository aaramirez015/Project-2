#pragma once
#include <vector>
#include <map>
#include <unordered_map>
#include "Transaction.h"
#include "AccountStats.h"

using namespace std;

class Analyzer {
public:
    //This function processes transactions using a map.
    static map<string, AccountStats> analyzeWithMap(const vector<Transaction>& transactions);

    //This function processes transactions using an unordered_map.
    static unordered_map<string, AccountStats> analyzeWithUnorderedMap(const vector<Transaction>& transactions);
};
