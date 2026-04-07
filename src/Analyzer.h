#pragma once
#include <vector>
#include "Transaction.h"
#include "OrderedMap.h"
#include "HashMap.h"
class Analyzer {
public:

    //this is building the ordered map
    static void analyzeWithMap(const std::vector<Transaction>& transactions, OrderedMap& accountMap);

    //Builds the hash map
    static void analyzeWithUnorderedMap(const std::vector<Transaction>& transactions, HashMap& accountMap);
};