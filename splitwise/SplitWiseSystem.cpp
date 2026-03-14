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
        throw SplitWiseException("[Error] Couldn't create user");
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
        throw SplitWiseException("[Error] Couldn't create group");
    }

    assert(group != nullptr);

    return *(group);
}

