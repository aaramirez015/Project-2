#include "AccountStats.h"

//This constructor initializes all account statistics.
AccountStats::AccountStats() {
    totalTransactions = 0;
    totalMoneySent = 0.0;
    totalMoneyReceived = 0.0;
    fraudCount = 0;
    flaggedFraudCount = 0;
}

//This function updates stats when the account sends money.
void AccountStats::addSentTransaction(const Transaction& transaction) {
    totalTransactions++;
    totalMoneySent += transaction.amount;

    //this tracks actual fraud for the sender.
    if (transaction.isFraud == 1) {
        fraudCount++;
    }

    //this tracks flagged fraud for the sender.
    if (transaction.isFlaggedFraud == 1) {
        flaggedFraudCount++;
    }
}

//This function updates stats when the account receives money.
void AccountStats::addReceivedTransaction(const Transaction& transaction) {
    totalTransactions++;
    totalMoneyReceived += transaction.amount;
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

//This function returns the flagged fraud count.
int AccountStats::getFlaggedFraudCount() const {
    return flaggedFraudCount;
}