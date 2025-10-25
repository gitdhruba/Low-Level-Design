#include "./Exception.hpp"

CacheException::CacheException(const std::string &msg) {
    this->message = msg;
}

CacheException::~CacheException() {}

const char * CacheException::what() const noexcept {
    return message.c_str();
}