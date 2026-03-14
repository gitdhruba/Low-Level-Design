#ifndef SPLITWISESYSTEM_HPP
#define SPLITWISESYSTEM_HPP

#include <map>

#include "./User.hpp"
#include "./Group.hpp"
#include "./Expense.hpp"
#include "./SplitType.hpp"

class SplitWiseSystem {
    private:
        std::map<uintptr_t, User*> users;
        std::map<uintptr_t, Group*> groups;
        std::map<uintptr_t, Expense*> expenses;
        std::map<uintptr_t, std::map<uintptr_t, double>> balances;

    public:
        SplitWiseSystem() {};
        ~SplitWiseSystem() {};

        const User& getUser(uintptr_t id) const;
        const Group& getGroup(uintptr_t id) const;

        const User& createUser(const std::string &name);
        const Group& createGroup(const std::string &name, const std::string &description, uintptr_t ownerId);

        bool deleteUser(uintptr_t id);
        bool deleteGroup(uintptr_t id);

        const Expense& createExpense(const std::string &description, uintptr_t payerId, double amount, const std::vector<std::pair<uintptr_t, double>> &shares, SplitType type);
        const Expense& createGroupExpense(uintptr_t groupId, const std::string &description, uintptr_t payerId, double amount, const std::vector<std::pair<uintptr_t, double>> &shares, SplitType type);
        bool updateExpense(uintptr_t id, const std::string &description, uintptr_t payerId, double amount, const std::vector<std::pair<uintptr_t, double>> &shares, SplitType type);
        bool deleteExpense(uintptr_t id);
};

#endif