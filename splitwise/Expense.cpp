#include "./Expense.hpp"
#include "./SplitWiseException.hpp"

Expense::Expense(const std::string &description, double amount, uintptr_t payerId, std::vector<std::pair<uintptr_t, double>> shares, SplitType splitType) {
    this->id = reinterpret_cast<uintptr_t>(this);
    this->description.assign(description);
    this->amount = amount;
    this->payerId = payerId;
    this->splitCalculator.reset(SplitCalculatorFactory::createSplitCalculator(splitType));

    if (!(this->splitCalculator->calculateSplits(amount, shares))) {
        throw SplitWiseException("[ERR] invalid splits calculation !");
    }
    
    this->amount = amount;
    this->shares.clear();
    for (const auto &it : shares) this->shares.insert(it);
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

double Expense::getShare(uintptr_t id) {
    return shares[id];
}


// setters
void Expense::setDescription(const std::string &description) {
    this->description.assign(description);
}

void Expense::setPayerId(uintptr_t payerId) {
    this->payerId = payerId;
}

bool Expense::updateExpense(double amount, std::vector<std::pair<uintptr_t, double>> shares, SplitType splitType) {
    this->splitCalculator.reset(SplitCalculatorFactory::createSplitCalculator(splitType));
    if (!(this->splitCalculator->calculateSplits(amount, shares))) {
        throw SplitWiseException("[ERR] invalid splits calculation !");
        return false;
    }
    
    this->amount = amount;
    this->shares.clear();
    for (const auto &it : shares) this->shares.insert(it);
    return true;
}