#pragma once
#include "Transaction.h"

//This class stores the statistics we need for a single account.
class AccountStats {
    private:
        int totalTransactions;
        double totalMoneySent;
        double totalMoneyReceived;
        int fraudCount;

    public:
        //This constructor initializes all account statistics.
        AccountStats();

        //This function updates stats when the account sends money.
        void addSentTransaction(const Transaction& transaction);

        //This function updates stats when the account receives money.
        void addReceivedTransaction(const Transaction& transaction);

        //Getter functions
        int getTotalTransactions() const;
        double getTotalMoneySent() const;
        double getTotalMoneyReceived() const;
        int getFraudCount() const;
};