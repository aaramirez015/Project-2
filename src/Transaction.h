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
    Transaction();
};