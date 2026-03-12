#include "./SplitCalculator.hpp"

static inline double to_2decimalplace(double x) {
    return ((long long)(x * 100)) / 100.0;
}

bool SplitCalculator::validateSplits(double amount, const std::map<uintptr_t, double> &shares) {
    double total = 0.0;
    for (const auto &it : shares) total += it.second;
    return (bool)(total == amount);
}

bool SplitCalculator::validateSplits(double amount, const std::vector<std::pair<uintptr_t, double>> &shares) {
    double total = 0.0;
    for (const auto &it : shares) total += it.second;
    return (bool)(total == amount);
}

bool EqualSplitCalculator::calculateSplits(double amount, std::vector<std::pair<uintptr_t, double>> &shares) {
    size_t n = shares.size();
    if (n <= 0) {
        throw SplitWiseException("[ERR] The number of participants should be greater than zero.");
        return false;
    }

    amount = to_2decimalplace(amount);
    double share = (amount / n);
    share = to_2decimalplace(share);
    double totalAssigned = 0.0;
    for (auto &it : shares) {
        it.second = share;
        totalAssigned += share;
    }

    double extra = amount - totalAssigned;
    shares[0].second += extra;

    return this->validateSplits(amount, shares);
}

bool PercentageSplitCalculator::calculateSplits(double amount, std::vector<std::pair<uintptr_t, double>> &shares) {
    size_t n = shares.size();
    if (n <= 0) {
        throw SplitWiseException("[ERR] The number of participants should be greater than zero.");
        return false;
    }

    long long total = 0ll;
    for (const auto &it : shares) {
        long long sharePercent = (long long)it.second;
        if (((double)sharePercent) != it.second) {
            throw SplitWiseException("[ERR] Percentage should be an integer.");
            return false;
        }

        if ((sharePercent < 0.0) || (sharePercent > 100.0)) {
            throw SplitWiseException("[ERR] Percentage should be in range [0, 100].");
            return false;
        }

        total += sharePercent;
    }

    if (total != 100ll) {
        throw SplitWiseException("[ERR] Percentage must sum up to 100.");
        return false;
    }

    amount = to_2decimalplace(amount);
    for (auto &it : shares) {
        long long sharePercent = (long long)it.second;
        it.second = (amount * sharePercent) / 100.0;
    }

    return this->validateSplits(amount, shares);
}

bool ExactSplitCalculator::calculateSplits(double amount, std::vector<std::pair<uintptr_t, double>> &shares) {
    size_t n = shares.size();
    if (n <= 0) {
        throw SplitWiseException("[ERR] The number of participants should be greater than zero.");
        return false;
    }

    amount = to_2decimalplace(amount);
    for (auto &it : shares) {
        it.second = to_2decimalplace(it.second);
    }

    return this->validateSplits(amount, shares);
}