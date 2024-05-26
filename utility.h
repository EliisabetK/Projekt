#ifndef UTILITY_H
#define UTILITY_H

#include <stdexcept>
#include <string>

class ViganeSymbol : public std::runtime_error {
public:
    explicit ViganeSymbol(const std::string& arg) : std::runtime_error(arg), sõnum(arg) {}

    const char* what() const noexcept override {
        return sõnum.c_str();
    }

private:
    std::string sõnum;
};

#endif // UTILITY_H
