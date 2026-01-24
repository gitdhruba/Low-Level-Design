#ifndef EXPENSE_HPP
#define EXPENSE_HPP

#include <cstdint>
#include <string>
#include <vector>
#include <map>

#include "./User.hpp"
#include "./SplitType.hpp"

class Expense {
    private:
        uintptr_t id;
        std::string description;
        double   amount;
        const User* payer;
        std::map<const User*, double> shares;
        SplitType  splitType;

    public:
        Expense(const std::string &description, double amount, const User *payer, std::vector<const User *> &participants, SplitType splitType);
        ~Expense();

        uintptr_t getId() const;
        const std::string& getDescription() const;
        double getAmount() const;
        const User* getPayer() const;
        const std::map<const User*, double>& getShares() const;
        const SplitType getSplitType() const;

        void setDescription(const std::string &description);
        void setAmount(double amount);
        void setPayer(const User *payer);
        void setShares(const std::map<const User*, double> &shares);
        void setShare(const User *participant, double amount);
        void setSplitType(SplitType splitType);

};

#endif
