#ifndef USER_HPP
#define USER_HPP

#include <cstdint>
#include <string>

class User {
    private:
        uintptr_t   id;
        std::string name;

    public:
        User(const std::string &name);
        ~User();

        uintptr_t getId() const;
        const std::string& getName() const;

};

#endif