#pragma once
#include <string>
#include <vector>
#include "Transaction.h"

class CSVReader {
    private:
        //This converts one csv line into one transaction object
        static Transaction parseLine(const std::string& line);
    public:
        //loads all transctions from csv file
        static std::vector<Transaction> loadTransactions(const std::string& filename);
};