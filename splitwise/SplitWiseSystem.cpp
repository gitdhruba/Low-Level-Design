#include <cassert>
#include <iostream>

#include "./SplitWiseSystem.hpp"
#include "./SplitWiseException.hpp"

SplitWiseSystem::SplitWiseSystem() {}

SplitWiseSystem::~SplitWiseSystem() {
    // delete transactions
    for (auto &it : transactions) {
        delete it.second;
        it.second = nullptr;
    }

    transactions.clear();
    userTransactions.clear();

    // delete expenses
    for (auto &it : expenses) {
        delete it.second;
        it.second = nullptr;
    }

    expenses.clear();

    // delete balances
    balances.clear();

    // delete groups
    for (auto &it : groups) {
        delete it.second;
        it.second = nullptr;
    }

    groups.clear();

    // delete users
    for (auto &it : users) {
        delete it.second;
        it.second = nullptr;
    }

    users.clear();
}

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

    // update balances
    const std::map<uintptr_t, double>& shares = expense->getShares();
    for (const auto &it : shares) {
        if (it.first != payerId) {
            balances[payerId][it.first] += it.second;
            balances[it.first][payerId] -= it.second;
        }
    }

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

    // update balances
    const std::map<uintptr_t, double>& shares = expense->getShares();
    for (const auto &it : shares) {
        if (it.first != payerId) {
            balances[payerId][it.first] += it.second;
            balances[it.first][payerId] -= it.second;
        }
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
    // update balances from old expense
    uintptr_t oldPayerId = expense.getPayerId();
    const std::map<uintptr_t, double>& oldShares = expense.getShares();
    for (const auto &it : oldShares) {
        if (it.first != oldPayerId) {
            balances[oldPayerId][it.first] -= it.second;
            balances[it.first][oldPayerId] += it.second;
        }
    }

    expense.setDescription(description);
    expense.setPayerId(payerId);
    bool res = expense.updateExpense(amount, shares, type);
    
    // update balances from new expense
    const std::map<uintptr_t, double>& newShares = expense.getShares();
    for (const auto &it : newShares) {
        if (it.first != payerId) {
            balances[payerId][it.first] += it.second;
            balances[it.first][payerId] -= it.second;
        }
    }

    return res;
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

bool SplitWiseSystem::doSettlement(uintptr_t expenseId, uintptr_t userId, double amount) {
    std::map<uintptr_t, Expense*>::iterator it = expenses.find(expenseId);
    if (it == expenses.end()) {
        throw SplitWiseException("[Error] Expense doesn't exist.");
    }

    if (users.find(userId) == users.end()) {
        throw SplitWiseException("[Error] User doesn't exist.");
    }

    Expense &expense = *(it->second);
    bool res = expense.doSettlement(userId, amount);
    if (res) {
        uintptr_t payerId = expense.getPayerId();

        // create a transaction
        Transaction *transaction = nullptr;
        try {
            transaction = new Transaction(userId, payerId, amount);
            transactions[transaction->getId()] = transaction;
        }
        catch (std::bad_alloc &e) {
            throw SplitWiseException("[Error] Couldn't create transaction.");
        }

        assert(transaction != nullptr);

        userTransactions[userId].push_back(transaction->getId());
        
        // update balance
        balances[payerId][userId] -= amount;
        balances[userId][payerId] += amount;
    }

    return res;
}

void SplitWiseSystem::printBalance(uintptr_t userId) {
    if (users.find(userId) == users.end()) {
        throw SplitWiseException("[Error] User doesn't exist.");
    }

    for (const auto &it : balances[userId]) {
        std::cout << "user id - " << it.first << "    " << "balance - " << it.second << std::endl;
    }
}