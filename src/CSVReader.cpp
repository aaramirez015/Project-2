#include "CSVReader.h"
#include <fstream>
#include <iostream>
#include <sstream>

//This helper converts one CSV line into a Transaction object.
Transaction CSVReader::parseLine(const std::string& line) {
    std::stringstream ss(line);
    std::string token;
    Transaction t;

    std::getline(ss, token, ',');
    t.step = std::stoll(token);

    std::getline(ss, t.type, ',');

    std::getline(ss, token, ',');
    t.amount = std::stod(token);

    std::getline(ss, t.nameOrig, ',');

    std::getline(ss, token, ',');
    t.oldbalanceOrg = std::stod(token);

    std::getline(ss, token, ',');
    t.newbalanceOrig = std::stod(token);

    std::getline(ss, t.nameDest, ',');

    std::getline(ss, token, ',');
    t.oldbalanceDest = std::stod(token);

    std::getline(ss, token, ',');
    t.newbalanceDest = std::stod(token);

    std::getline(ss, token, ',');
    t.isFraud = std::stoi(token);

    std::getline(ss, token, ',');
    t.isFlaggedFraud = std::stoi(token);

    return t;
}

//This loads all transactions from the CSV file into a vector.
std::vector<Transaction> CSVReader::loadTransactions(const std::string& filename) {
    std::vector<Transaction> transactions;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: could not open file." << std::endl;
        return transactions;
    }

    std::string line;

    //Skip the header line.
    std::getline(file, line);

    //Read the remaining lines.
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        Transaction t = parseLine(line);
        transactions.push_back(t);
    }

    return transactions;
}