#include "./Group.hpp"

Group::Group(const std::string &name, const std::string &description, const User *owner) {
    this->id = reinterpret_cast<uintptr_t>(this);
    this->name.assign(name);
    this->description.assign(description);
    this->owner = owner;
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

const User* Group::getOwner() const {
    return owner;
}

const std::set<const User *>& Group::getMembers() const {
    return members;
}


// setters
void Group::setName(const std::string &name) {
    this->name.assign(name);
}

void Group::setDescription(const std::string &description) {
    this->description.assign(description);
}

bool Group::addMember(const User *member) {
    return this->members.insert(member).second;
}

bool Group::removeMember(const User *member) {
    std::set<const User *>::iterator it = members.find(member);
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