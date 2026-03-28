#include "FraudDetector.h"

//this function calculates the score for one account.
double FraudDetector::calculateFraudScore(const AccountStats& stats) {
    double score = 0.0;

    //adds points based on total transactions.
    score += stats.getTotalTransactions() * 0.5;

    //adds points based on money sent.
    score += stats.getTotalMoneySent() / 10000.0;

    //adds points based on money received.
    score += stats.getTotalMoneyReceived() / 20000.0;

    //fraud count has biggest impact.
    score += stats.getFraudCount() * 100.0;

    //extra points for high money sent.
    if (stats.getTotalMoneySent() >= 100000.0) {
        score += 25.0;
    }

    if (stats.getTotalMoneySent() >= 1000000.0) {
        score += 50.0;
    }

    //extra points for high money received.
    if (stats.getTotalMoneyReceived() >= 100000.0) {
        score += 15.0;
    }

    if (stats.getTotalMoneyReceived() >= 1000000.0) {
        score += 30.0;
    }

    return score;
}

//this function checks if an account looks sus.
bool FraudDetector::isSus(const AccountStats& stats) {

    //if account has any fraud it is sus.
    if (stats.getFraudCount() > 0) {
        return true;
    }

    //large number of transactions.
    if (stats.getTotalTransactions() >= 25) {
        return true;
    }

    //large amount of money sent.
    if (stats.getTotalMoneySent() >= 100000.0) {
        return true;
    }

    return false;
}

//this function creates fraud score from a map.
map<string, double> FraudDetector::buildScoresFromMap(const map<string, AccountStats>& accountStats) {
    map<string, double> scores;

    //loops through each account in map.
    for (const auto& pair : accountStats) {
        string name = pair.first;
        const AccountStats& stats = pair.second;

        scores[name] = calculateFraudScore(stats);
    }

    return scores;
}

//this function creates fraud scores from an unordered_map.
unordered_map<string, double> FraudDetector::buildScoresFromUnorderedMap(const unordered_map<string, AccountStats>& accountStats) {
    unordered_map<string, double> scores;

    //loops through each account in unordered_map.
    for (const auto& pair : accountStats) {
        string name = pair.first;
        const AccountStats& stats = pair.second;

        scores[name] = calculateFraudScore(stats);
    }

    return scores;
}