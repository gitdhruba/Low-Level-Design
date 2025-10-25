#ifndef EXCEPTION_HDR

#define EXCEPTION_HDR

#include <bits/exception.h>
#include <string>

class CacheException : public std::exception {
private:
    std::string message;

public:
    CacheException(const std::string &msg);
    ~CacheException();

    const char * what() const noexcept override;
};

#endif