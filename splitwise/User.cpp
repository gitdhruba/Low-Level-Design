#include "./User.hpp"

User::User(const std::string& name) {
    this->id = reinterpret_cast<uintptr_t>(this);
    this->name.assign(name);
}

User::~User() {

}

uintptr_t User::getId() const {
    return id;
}

const std::string& User::getName() const {
    return name;
}
