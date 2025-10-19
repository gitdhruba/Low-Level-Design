#ifndef EXCEPTION_HDR

#define EXCEPTION_HDR

#include <bits/exception.h>
#include <string>

class SnakeLadderException : public std::exception {
private:
    std::string message;

public:
    SnakeLadderException(const std::string &msg);
    ~SnakeLadderException();

    const char * what() const noexcept override;
};

#endif