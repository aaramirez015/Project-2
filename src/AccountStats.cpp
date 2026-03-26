#include "AccountStats.h"

//This constructor initializes all account statistics.
AccountStats::AccountStats() {
    totalTransactions = 0;
    totalMoneySent = 0.0;
    totalMoneyReceived = 0.0;
    fraudCount = 0;
}

//This function updates stats when the account sends money.
void AccountStats::addSentTransaction(const Transaction& transaction) {
    totalTransactions++;
    totalMoneySent += transaction.amount;

    if (transaction.isFraud == 1 || transaction.isFlaggedFraud == 1) {
        fraudCount++;
    }
}

//This function updates stats when the account receives money.
void AccountStats::addReceivedTransaction(const Transaction& transaction) {
    totalTransactions++;
    totalMoneyReceived += transaction.amount;

    if (transaction.isFraud == 1 || transaction.isFlaggedFraud == 1) {
        fraudCount++;
    }
}

//This function returns the total number of transactions.
int AccountStats::getTotalTransactions() const {
    return totalTransactions;
}

//This function returns the total money sent.
double AccountStats::getTotalMoneySent() const {
    return totalMoneySent;
}

//This function returns the total money received.
double AccountStats::getTotalMoneyReceived() const {
    return totalMoneyReceived;
}

//This function returns the fraud count.
int AccountStats::getFraudCount() const {
    return fraudCount;
}