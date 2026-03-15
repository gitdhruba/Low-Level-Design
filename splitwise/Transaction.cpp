#include "./Transaction.hpp"

Transaction::Transaction(uintptr_t payerId, uintptr_t payeeId, double amount) {
    this->id = reinterpret_cast<uintptr_t>(this);
    this->payerId = payerId;
    this->payeeId = payeeId;
    this->amount = amount;
}

Transaction::~Transaction() {}

// getters
uintptr_t Transaction::getId() const {
    return id;
}

uintptr_t Transaction::getPayerId() const {
    return payerId;
}

uintptr_t Transaction::getPayeeId() const {
    return payeeId;
}

double Transaction::getAmount() const {
    return amount;
}

// setters
void Transaction::setPayerId(uintptr_t id) {
    this->payerId = id;
}

void Transaction::setPayeeId(uintptr_t id) {
    this->payeeId = payeeId;
}

void Transaction::setAmount(double amount) {
    this->amount = amount;
}
