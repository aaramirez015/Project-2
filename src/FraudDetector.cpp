#include "FraudDetector.h"

//this function calculates the score for one account.
double FraudDetector::calculateFraudScore(const AccountStats& stats) {
    double score = 0.0;

    //actual fraud matters the most.
    score += stats.getFraudCount() * 1200.0;

    //flagged fraud also matters, but less.
    score += stats.getFlaggedFraudCount() * 400.0;

    //more transactions increase suspicion.
    score += stats.getTotalTransactions() * 8.0;

    //high sent amounts add more suspicion.
    if (stats.getTotalMoneySent() >= 10000.0) {
        score += 25.0;
    }
    if (stats.getTotalMoneySent() >= 100000.0) {
        score += 50.0;
    }
    if (stats.getTotalMoneySent() >= 1000000.0) {
        score += 100.0;
    }
    if (stats.getTotalMoneySent() >= 10000000.0) {
        score += 200.0;
    }

    //received money still matters a little.
    if (stats.getTotalMoneyReceived() >= 100000.0) {
        score += 10.0;
    }
    if (stats.getTotalMoneyReceived() >= 1000000.0) {
        score += 20.0;
    }

    //this helps break ties between similar accounts.
    score += stats.getTotalMoneySent() / 10000000.0;

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