#pragma once
#include <string>
#include "AccountStats.h"

class FraudDetector {
public:
    //this function calculates the score for one account.
    static double calculateFraudScore(const AccountStats& stats);

    //this function checks if an account looks sus.
    static bool isSus(const AccountStats& stats);
};