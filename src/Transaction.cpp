#include "Transaction.h"

//This constructor initializes all transaction fields to default values.
Transaction::Transaction() {
    step = 0;
    type = "";
    amount = 0.0;
    nameOrig = "";
    oldbalanceOrg = 0.0;
    newbalanceOrig = 0.0;
    nameDest = "";
    oldbalanceDest = 0.0;
    newbalanceDest = 0.0;
    isFraud = 0;
    isFlaggedFraud = 0;
}