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
        const User* owner;
        std::set<const User *> members;
        std::set<const Expense *> expenses;


    public:
        Group(const std::string &name, const std::string &description, const User *owner);
        ~Group();

        uintptr_t getId() const;
        const std::string& getName() const;
        const std::string& getDescription() const;
        const User* getOwner() const;
        const std::set<const User *>& getMembers() const;
        const std::set<const Expense *>& getExpenses() const;

        void setName(const std::string &name);
        void setDescription(const std::string &description);
        void setMembers(const std::vector<const User *> &members);
        bool addMember(const User *member);
        bool removeMember(const User *member);
        void addExpense(const Expense *expense);
};

#endif