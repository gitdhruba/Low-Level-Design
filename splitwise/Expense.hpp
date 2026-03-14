#ifndef EXPENSE_HPP
#define EXPENSE_HPP

#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <memory>

#include "./User.hpp"
#include "./SplitCalculator.hpp"

class Expense {     
    private:
        uintptr_t id;
        std::string description;
        uintptr_t groupId;
        uintptr_t payerId;
        double   amount;
        bool isSettled;
        std::map<uintptr_t, double> shares;
        std::unique_ptr<SplitCalculator>  splitCalculator;

    public:
        Expense(const std::string &description, uintptr_t groupId, uintptr_t payerId, double amount, std::vector<std::pair<uintptr_t, double>> shares, SplitType splitType);
        ~Expense();

        uintptr_t getId() const;
        const std::string& getDescription() const;
        double getAmount() const;
        uintptr_t getPayerId() const;
        uintptr_t getGroupId() const;
        double getShare(uintptr_t id);
        bool isSettledUp() const;

        void setDescription(const std::string &description);
        void setPayerId(uintptr_t payerId);
        bool updateExpense(double amount, std::vector<std::pair<uintptr_t, double>> shares, SplitType splitType);

};

#endif
