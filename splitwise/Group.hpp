#ifndef GROUP_HPP
#define GROUP_HPP

#include <cstdint>
#include <string>
#include <set>

#include "./User.hpp"
#include "./Expense.hpp"

class Group {
    private:
        uintptr_t   id;
        std::string name;
        std::string description;
        uintptr_t ownerId;
        std::set<uintptr_t> members;
        std::set<uintptr_t> expenses;


    public:
        Group(const std::string &name, const std::string &description, uintptr_t ownerId);
        ~Group();

        uintptr_t getId() const;
        const std::string& getName() const;
        const std::string& getDescription() const;
        uintptr_t getOwnerId() const;
        const std::set<uintptr_t>& getMembers() const;
        const std::set<uintptr_t>& getExpenses() const;

        void setName(const std::string &name);
        void setDescription(const std::string &description);
        void setMembers(const std::vector<uintptr_t> &members);
        bool addMember(uintptr_t memberId);
        bool removeMember(uintptr_t memberId);
        void addExpense(uintptr_t expenseId);
};

#endif