#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <cstdint>

class Transaction {
    private:
        uintptr_t id;
        uintptr_t payerId;
        uintptr_t payeeId;
        double amount;

    public:
        Transaction(uintptr_t payerId, uintptr_t payeeId, double amount);
        ~Transaction();

        uintptr_t getId() const;
        uintptr_t getPayerId() const;
        uintptr_t getPayeeId() const;
        double getAmount() const;

        void setPayerId(uintptr_t id);
        void setPayeeId(uintptr_t id);
        void setAmount(double amount);
};

#endif