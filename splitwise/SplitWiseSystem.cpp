#include <cassert>

#include "./SplitWiseSystem.hpp"
#include "./SplitWiseException.hpp"

const User& SplitWiseSystem::getUser(uintptr_t id) const {
    std::map<uintptr_t, User*>::const_iterator it = users.find(id);
    if (it == users.end()) {
        throw SplitWiseException("[Error] User does not exist.");
    }

    return *(it->second);
}

const Group& SplitWiseSystem::getGroup(uintptr_t id) const {
    std::map<uintptr_t, Group*>::const_iterator it = groups.find(id);
    if (it == groups.end()) {
        throw SplitWiseException("[Error] Group does not exist.");
    }

    return *(it->second);
}

const User& SplitWiseSystem::createUser(const std::string &name) {
    User *user = nullptr;

    try {
        user = new User(name);
        users[user->getId()] = user;
    }
    catch (std::bad_alloc &e) {
        throw SplitWiseException("[Error] Couldn't create user.");
    }

    assert(user != nullptr);

    return *(user);
}

const Group& SplitWiseSystem::createGroup(const std::string &name, const std::string &description, uintptr_t ownerId) {
    Group *group = nullptr;
    std::map<uintptr_t, User*>::const_iterator it = users.find(ownerId);
    if (it == users.end()) {
        throw SplitWiseException("[Error] Owner does not exist.");
    }

    try {
        group = new Group(name, description, ownerId);
        groups[group->getId()] = group;
    }
    catch (std::bad_alloc &e) {
        throw SplitWiseException("[Error] Couldn't create group.");
    }

    assert(group != nullptr);

    return *(group);
}

bool SplitWiseSystem::deleteUser(uintptr_t id) {
    std::map<uintptr_t, User*>::iterator it = users.find(id);
    if (it == users.end()) {
        throw SplitWiseException("[Error] User does not exist.");
    }

    // check if the user is a part of any group
    for (const auto &it: groups) {
        const std::set<uintptr_t> &members = it.second->getMembers();
        for (uintptr_t memberId: members) {
            if (memberId == id) {
                throw SplitWiseException("[Error] User is a part of existing group.");
            }
        }
    }

    // check if user has any unsettled balances
    for (const auto &it: balances[id]) {
        if (it.second != 0.0) {
            throw SplitWiseException("[Error] User has unsettled balances.");
        }
    }

    delete it->second;
    it->second = nullptr;
    return (users.erase(id) >= 0);
}

bool SplitWiseSystem::deleteGroup(uintptr_t id) {
    std::map<uintptr_t, Group*>::iterator it = groups.find(id);
    if (it == groups.end()) {
        throw SplitWiseException("[Error] Group does not exist.");
    }

    // check if user has any unsettled expenses
    for (uintptr_t expenseId: it->second->getExpenses()) {
        if (!expenses[expenseId]->isSettledUp()) {
            throw SplitWiseException("[Error] Group has unsettled expenses.");
        }
    }

    delete it->second;
    it->second = nullptr;
    return (groups.erase(id) >= 0);
}

const Expense& SplitWiseSystem::createExpense(const std::string &description, uintptr_t payerId, double amount, const std::vector<std::pair<uintptr_t, double>> &shares, SplitType type) {
    std::map<uintptr_t, User*>::iterator it = users.find(payerId);
    if (it == users.end()) {
        throw SplitWiseException("[Error] Payer does not exist.");
    }

    for (const auto &it : shares) {
        std::map<uintptr_t, User*>::iterator itr = users.find(it.first);
        if (itr == users.end()) {
            throw SplitWiseException("[Error] Share holder does not exist.");
        }
    }

    Expense *expense = nullptr;
    try {
        expense = new Expense(description, 0ul, payerId, amount, shares, type);
        expenses[expense->getId()] = expense;
    }
    catch (std::bad_alloc &e) {
        throw SplitWiseException("[Error] Couldn't create expense.");
    }

    assert(expense != nullptr);

    return *(expense);
}

const Expense& SplitWiseSystem::createGroupExpense(uintptr_t groupId, const std::string &description, uintptr_t payerId, double amount, const std::vector<std::pair<uintptr_t, double>> &shares, SplitType type) {
    std::map<uintptr_t, Group*>::iterator it = groups.find(groupId);
    if (it == groups.end()) {
        throw SplitWiseException("[Error] Group does not exist.");
    }

    std::map<uintptr_t, User*>::iterator itr = users.find(payerId);
    if (itr == users.end()) {
        throw SplitWiseException("[Error] Payer does not exist.");
    }

    for (const auto &it : shares) {
        itr = users.find(it.first);
        if (itr == users.end()) {
            throw SplitWiseException("[Error] Share holder does not exist.");
        }
    }

    Expense *expense = nullptr;
    try {
        expense = new Expense(description, groupId, payerId, amount, shares, type);
        expenses[expense->getId()] = expense;
    }
    catch (std::bad_alloc &e) {
        throw SplitWiseException("[Error] Couldn't create expense.");
    }

    assert(expense != nullptr);

    if (!it->second->addExpense(expense->getId())) {
        throw SplitWiseException("[Error] Couldn't add expense to the group.");
    }

    return *(expense);
}

bool SplitWiseSystem::updateExpense(uintptr_t id, const std::string &description, uintptr_t payerId, double amount, const std::vector<std::pair<uintptr_t, double>> &shares, SplitType type) {
    std::map<uintptr_t, Expense*>::iterator it = expenses.find(id);
    if (it == expenses.end()) {
        throw SplitWiseException("[Error] Expense doesn't exist.");
    }

    std::map<uintptr_t, User*>::iterator itr = users.find(payerId);
    if (itr == users.end()) {
        throw SplitWiseException("[Error] Payer does not exist.");
    }

    Expense &expense = *(it->second);
    expense.setDescription(description);
    expense.setPayerId(payerId);
    return expense.updateExpense(amount, shares, type);
}

bool SplitWiseSystem::deleteExpense(uintptr_t id) {
    std::map<uintptr_t, Expense*>::iterator it = expenses.find(id);
    if (it == expenses.end()) {
        throw SplitWiseException("[Error] Expense doesn't exist.");
    }

    // check whether it is settled up
    Expense &expense = *(it->second);
    if (!expense.isSettledUp()) {
        throw SplitWiseException("[Error] Expense is not settled up.");
    }

    // remove it from group if it is a group expense
    if (expense.getGroupId()) {
        Group &group = *(groups[expense.getGroupId()]);
        group.removeExpense(id);
    }
    
    delete it->second;
    it->second = nullptr;
    return (expenses.erase(id) > 0);
}

