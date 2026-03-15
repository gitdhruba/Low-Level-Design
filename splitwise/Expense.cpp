#include "./Expense.hpp"
#include "./SplitWiseException.hpp"

Expense::Expense(const std::string &description, uintptr_t groupId, uintptr_t payerId, double amount, std::vector<std::pair<uintptr_t, double>> shares, SplitType splitType) {
    if (amount <= 0.0) {
        throw SplitWiseException("[ERR] Amount should be greater than 0 !");
    }
    
    this->id = reinterpret_cast<uintptr_t>(this);
    this->description.assign(description);
    this->amount = amount;
    this->payerId = payerId;
    this->groupId = groupId;
    this->splitCalculator.reset(SplitCalculatorFactory::createSplitCalculator(splitType));

    if (!(this->splitCalculator->calculateSplits(amount, shares))) {
        throw SplitWiseException("[ERR] invalid splits calculation !");
    }
    
    this->amount = amount;
    this->shares.clear();
    for (const auto &it : shares) this->shares.insert(it);
    this->shares[payerId] = 0.0;
}

Expense::~Expense() {

}


// getters
uintptr_t Expense::getId() const {
    return id;
}

const std::string& Expense::getDescription() const {
    return description;
}

double Expense::getAmount() const {
    return amount;
}

uintptr_t Expense::getPayerId() const {
    return payerId;
}

uintptr_t Expense::getGroupId() const {
    return groupId;
}

const std::map<uintptr_t, double>& Expense::getShares() const {
    return shares;
}

double Expense::getShare(uintptr_t id) {
    return shares[id];
}

bool Expense::isSettledUp() const {
    double total = 0.0;
    for (const auto &it : shares) total += it.second;

    return (bool)(total <= 0.0);
}

// setters
void Expense::setDescription(const std::string &description) {
    this->description.assign(description);
}

void Expense::setPayerId(uintptr_t payerId) {
    this->payerId = payerId;
}

bool Expense::updateExpense(double amount, std::vector<std::pair<uintptr_t, double>> shares, SplitType splitType) {
    if (amount <= 0.0) {
        throw SplitWiseException("[ERR] Amount should be greater than 0 !");
    }

    this->splitCalculator.reset(SplitCalculatorFactory::createSplitCalculator(splitType));
    if (!(this->splitCalculator->calculateSplits(amount, shares))) {
        throw SplitWiseException("[ERR] invalid splits calculation !");
        return false;
    }
    
    this->amount = amount;
    this->shares.clear();
    for (const auto &it : shares) this->shares.insert(it);
    this->shares[payerId] = 0.0;

    return true;
}

bool Expense::doSettlement(uintptr_t shareHolderId, double amount) {
    std::map<uintptr_t, double>::iterator it = shares.find(shareHolderId);

    if (it == shares.end()) {
        throw SplitWiseException("[Error] Share holder is not a part of this expense.");
    }

    if (shareHolderId != this->payerId) {
        double &share = it->second;
        if (share == amount) {
            share = 0.0;
            return true;
        }
    }

    return false;
}