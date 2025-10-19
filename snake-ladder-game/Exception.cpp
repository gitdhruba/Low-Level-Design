#include "./Exception.hpp"

SnakeLadderException::SnakeLadderException(const std::string &msg) {
    this->message = msg;
}

SnakeLadderException::~SnakeLadderException() {}

const char * SnakeLadderException::what() const noexcept {
    return message.c_str();
}