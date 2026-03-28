#include <iostream>
#include <vector>
#include "CSVReader.h"
#include "Analyzer.h"
#include "FraudDetector.h"
#include "Transaction.h"
#include <chrono>
#include <queue>
#include <utility>

using namespace std;

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

    //build fraud scores from both structures
    map<string, double> mapScores = FraudDetector::buildScoresFromMap(mapResult);
    unordered_map<string, double> unorderedScores = FraudDetector::buildScoresFromUnorderedMap(unorderedResult);

    //This heap stores score first and account name second.
    priority_queue<pair<double, string>> maxHeap;

    //This loop pushes all map scores into the heap.
    for (const auto& pair : mapScores) {
        string name = pair.first;
        double score = pair.second;

        maxHeap.push({score, name});
    }

    //Print timing results
    auto mapTime = chrono::duration_cast<chrono::milliseconds>(endMap - startMap);
    auto unorderedTime = chrono::duration_cast<chrono::milliseconds>(endUnordered - startUnordered);

    cout << "Map processing time: " << mapTime.count() << " ms" << endl;
    cout << "Unordered_map processing time: " << unorderedTime.count() << " ms" << endl;
    cout << "difference in time: " << mapTime.count() - unorderedTime.count() << " ms" << endl;

    cout << "accounts scored with map: " << mapScores.size() << endl;
    cout << "accounts scored with unordered_map: " << unorderedScores.size() << endl;

    cout << endl;
    cout << "Top suspicious accounts:" << endl;

    int count = 0;

    //This loop prints the top 10 suspicious accounts.
    while (!maxHeap.empty() && count < 10) {
        pair<double, string> cur = maxHeap.top();
        maxHeap.pop();

        string name = cur.second;
        double score = cur.first;
        AccountStats stats = mapResult[name];

        cout << count + 1 << ". " << name << endl;
        cout << "   score: " << score << endl;
        cout << "   total transactions: " << stats.getTotalTransactions() << endl;
        cout << "   total money sent: " << stats.getTotalMoneySent() << endl;
        cout << "   total money received: " << stats.getTotalMoneyReceived() << endl;
        cout << "   fraud count: " << stats.getFraudCount() << endl;
        cout << "   flagged fraud count: " << stats.getFlaggedFraudCount() << endl;
        cout << endl;

        count++;
    }

    return 0;
}