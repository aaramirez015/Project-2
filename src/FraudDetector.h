#pragma once
#include <map>
#include <unordered_map>
#include <string>
#include"AccountStats.h"

using namespace std;

class FraudDetector {
    public:
        //this function calculates the score for one account.
        static double calculateFraudScore(const AccountStats& stats);

        //this function checks if an account looks sus.
        static bool isSus(const AccountStats& stats);

        //this function creates fraud score from a map.
        static map<string, double> buildScoresFromMap(const map<string, AccountStats>& accountStats);

        //this function creates fraud scores from an unordered_map.
        static unordered_map<string, double> buildScoresFromUnorderedMap(const unordered_map<string, AccountStats>& accountStats);
};