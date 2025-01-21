#include <string>
#include <regex>

#include "string_utils.hpp"

bool StringUtils::IsInvalidNickname(const std::string &nickname) {
    std::regex pattern("^[a-zA-Z0-9]+$");
    return !(std::regex_match(nickname, pattern));
}

bool StringUtils::IsInvalidName(const std::string &name) {
    std::regex pattern("^[a-zA-Z ]+$");
    return !(std::regex_match(name, pattern));
}