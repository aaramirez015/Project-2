#include <iostream>
#include <vector>
#include "CSVReader.h"
#include "Analyzer.h"
#include "FraudDetector.h"
#include "Transaction.h"
#include "OrderedMap.h"
#include "HashMap.h"
#include <chrono>
#include <queue>
#include <utility>
#include <iomanip>
#include <string>

using namespace std;

int main() {
    vector<Transaction> transactions = CSVReader::loadTransactions("../data/fraud.csv");

    cout << fixed << setprecision(2);

    if (transactions.empty()) {
        cout << "Error: dataset not found. Please check README for setup." << endl;
        return 1;
    }

    cout << "Loaded transactions: " << transactions.size() << endl;

    //these are the custom data structures to hold account stats
    OrderedMap mapResult;
    HashMap unorderedResult;

    //MAP timing
    auto startMap = chrono::high_resolution_clock::now();
    Analyzer::analyzeWithMap(transactions, mapResult);
    auto endMap = chrono::high_resolution_clock::now();

    //UNORDERED MAP timing
    auto startUnordered = chrono::high_resolution_clock::now();
    Analyzer::analyzeWithUnorderedMap(transactions, unorderedResult);
    auto endUnordered = chrono::high_resolution_clock::now();

    //Print timing results
    auto mapTime = chrono::duration_cast<chrono::milliseconds>(endMap - startMap);
    auto unorderedTime = chrono::duration_cast<chrono::milliseconds>(endUnordered - startUnordered);

    int choice = 0;

    while (choice != 3) {
        cout << endl;
        cout << "Menu:" << endl;
        cout << "1. Show performance comparison" << endl;
        cout << "2. Show top suspicious accounts" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << endl;
            cout << "Map processing time: " << mapTime.count() << " ms" << endl;
            cout << "Unordered_map processing time: " << unorderedTime.count() << " ms" << endl;
            cout << "difference in time: " << mapTime.count() - unorderedTime.count() << " ms" << endl;
            cout << "accounts scored with map: " << mapResult.size() << endl;
            cout << "accounts scored with unordered_map: " << unorderedResult.size() << endl;
        }
        else if (choice == 2) {
            //This heap stores score first and account name second.
            priority_queue<pair<double, string>> maxHeap;

            //This loop pushes all map scores into the heap using forEach.
            mapResult.forEach([&](const string& name, const AccountStats& stats) {
                double score = FraudDetector::calculateFraudScore(stats);
                maxHeap.push({score, name});
            });

            cout << endl;
            cout << "Top suspicious accounts:" << endl;

            int count = 0;

            //This loop prints the top 10 suspicious accounts.
            while (!maxHeap.empty() && count < 10) {
                pair<double, string> cur = maxHeap.top();
                maxHeap.pop();

                string name = cur.second;
                double score = cur.first;

                //this is looking up the stats from the map using find.
                const AccountStats* statsPtr = mapResult.find(name);

                if (statsPtr == nullptr) {
                    continue;
                }

                cout << count + 1 << ". " << name << endl;
                cout << "   score: " << score << endl;
                cout << "   total transactions: " << statsPtr->getTotalTransactions() << endl;
                cout << "   total money sent: " << statsPtr->getTotalMoneySent() << endl;
                cout << "   total money received: " << statsPtr->getTotalMoneyReceived() << endl;
                cout << "   fraud count: " << statsPtr->getFraudCount() << endl;
                cout << "   flagged fraud count: " << statsPtr->getFlaggedFraudCount() << endl;
                cout << endl;

                count++;
            }
        }
        else if (choice == 3) {
            cout << "Exiting program." << endl;
        }
        else {
            cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}