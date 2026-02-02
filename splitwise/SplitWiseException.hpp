#ifndef SPLITWISEEXCEPTION_HPP
#define SPLITWISEEXCEPTION_HPP

#include <exception>
#include <string>

class SplitWiseException : public std::exception {
    private:
        std::string message;

    public:
        SplitWiseException(const std::string &message) {
            this->message.assign(message);
        }

        virtual ~SplitWiseException() {}

        const char * what() const noexcept final {
            return message.c_str();
        }
};

#endif