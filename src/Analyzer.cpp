#include "Analyzer.h"

//This function processes transactions using a map.
map<string, AccountStats> Analyzer::analyzeWithMap(const vector<Transaction>& transactions) {
    map<string, AccountStats> accountMap;

    for (const Transaction& t : transactions) {
        //Update sender
        accountMap[t.nameOrig].addSentTransaction(t);

        //Update receiver
        accountMap[t.nameDest].addReceivedTransaction(t);
    }

    return accountMap;
}

//This function processes transactions using an unordered_map.
unordered_map<string, AccountStats> Analyzer::analyzeWithUnorderedMap(const vector<Transaction>& transactions) {
    unordered_map<string, AccountStats> accountMap;

    for (const Transaction& t : transactions) {
        //Update sender
        accountMap[t.nameOrig].addSentTransaction(t);

        //Update receiver
        accountMap[t.nameDest].addReceivedTransaction(t);
    }

    return accountMap;
}
