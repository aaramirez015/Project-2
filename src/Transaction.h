#pragma once
#include <string>

//This struct stores one transaction from the dataset
struct Transaction {
    long long step;
    std::string type;
    double amount;
    std::string nameOrig;
    double oldbalanceOrg;
    double newbalanceOrig;
    std::string nameDest;
    double oldbalanceDest;
    double newbalanceDest;
    int isFraud;
    int isFlaggedFraud;

    //Def constructor
    Transaction() {
        step = 0;
        amount = 0;
        oldbalanceOrg = (0.0);
        newbalanceOrig = (0.0);
        oldbalanceDest = (0.0);
        newbalanceDest = (0.0);
        isFraud = 0;
        isFlaggedFraud = 0;
    }
};