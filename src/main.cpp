#include <iostream>
#include <vector>
#include "CSVReader.h"
#include "Analyzer.h"
#include <chrono>

int main() {
    vector<Transaction> transactions = CSVReader::loadTransactions("../data/fraud.csv");

    cout << "Loaded transactions: " << transactions.size() << endl;

    //MAP timing
    auto startMap = chrono::high_resolution_clock::now();
    map<string, AccountStats> mapResult = Analyzer::analyzeWithMap(transactions);
    auto endMap = chrono::high_resolution_clock::now();

    //UNORDERED MAP timing
    auto startUnordered = chrono::high_resolution_clock::now();
    unordered_map<string, AccountStats> unorderedResult = Analyzer::analyzeWithUnorderedMap(transactions);
    auto endUnordered = chrono::high_resolution_clock::now();

    //Print timing results
    auto mapTime = chrono::duration_cast<chrono::milliseconds>(endMap - startMap);
    auto unorderedTime = chrono::duration_cast<chrono::milliseconds>(endUnordered - startUnordered);

    cout << "Map processing time: " << mapTime.count() << " ms" << endl;
    cout << "Unordered_map processing time: " << unorderedTime.count() << " ms" << endl;

    return 0;
}