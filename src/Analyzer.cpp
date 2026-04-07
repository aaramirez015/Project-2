#include "Analyzer.h"

//This is analyzing transactions with the ordered map
void Analyzer::analyzeWithMap(const std::vector<Transaction>& transactions, OrderedMap& accountMap) {
    for (const Transaction& t : transactions) {

        //this is updating sender statistics
        accountMap[t.nameOrig].addSentTransaction(t);

        //Updates receiver statistics
        accountMap[t.nameDest].addReceivedTransaction(t);
    }
}

//this is analyzing transactions with the hash map
void Analyzer::analyzeWithUnorderedMap(const std::vector<Transaction>& transactions, HashMap& accountMap) {
    for (const Transaction& t : transactions) {

        //this is updating sender statistics
        accountMap[t.nameOrig].addSentTransaction(t);

        //Updates receiver statistics
        accountMap[t.nameDest].addReceivedTransaction(t);
    }
}