#include "./Group.hpp"
#include "./SplitWiseException.hpp"

Group::Group(const std::string &name, const std::string &description, uintptr_t ownerId) {
    this->id = reinterpret_cast<uintptr_t>(this);
    this->name.assign(name);
    this->description.assign(description);
    this->ownerId = ownerId;
    if (this->members.insert(ownerId).second == false) {
        throw SplitWiseException("[Error] Couldn't add owner to the members.");
    }
}

Group::~Group() {}

// getters
uintptr_t Group::getId() const {
    return id;
}

const std::string& Group::getName() const {
    return name;
}

const std::string& Group::getDescription() const {
    return description;
}

uintptr_t Group::getOwnerId() const {
    return ownerId;
}

const std::set<uintptr_t>& Group::getMembers() const {
    return members;
}

const std::set<uintptr_t>& Group::getExpenses() const {
    return expenses;
}

// setters
void Group::setName(const std::string &name) {
    this->name.assign(name);
}

void Group::setDescription(const std::string &description) {
    this->description.assign(description);
}

bool Group::addMember(uintptr_t memberId) {
    return this->members.insert(memberId).second;
}

bool Group::removeMember(uintptr_t memberId) {
    std::set<uintptr_t>::const_iterator it = members.find(memberId);
    if (it != members.end()) {
        // logic for checking whether there is any debt remaining for this member
        // .....

        members.erase(it);
        return true;
    }
    else {
        return false;
    }
}

bool Group::addExpense(uintptr_t expenseId) {
    return this->expenses.insert(expenseId).second;
}

bool Group::removeExpense(uintptr_t expenseId) {
    return (this->expenses.erase(expenseId) > 0);
}