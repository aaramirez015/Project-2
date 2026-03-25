#include <iostream>
#include <vector>
#include "CSVReader.h"

int main() {
    std::vector<Transaction> transactions = CSVReader::loadTransactions("data/fraud.csv");

    std::cout << "Loaded transactions: " << transactions.size() << std::endl;

    //Print the first few transactions to make sure everything loaded correctly.
    for (size_t i = 0; i < transactions.size() && i < 5; i++) {
        std::cout << transactions[i].nameOrig << " -> "
                  << transactions[i].nameDest << " | "
                  << transactions[i].amount << " | "
                  << transactions[i].isFraud << std::endl;
    }

    return 0;
}