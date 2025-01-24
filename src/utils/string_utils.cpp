#include <string>
#include <regex>

#include "string_utils.hpp"

/**
 * @brief Checks if the given nickname is invalid.
 *
 * An invalid nickname is defined as either an empty string or
 * a string that contains spaces.
 *
 * @param nickname The nickname to be validated.
 * @return true if the nickname is invalid, false otherwise.
 */
bool StringUtils::IsInvalidNickname(const std::string &nickname) {
    std::regex pattern("^[a-zA-Z0-9]+$");
    return !(std::regex_match(nickname, pattern));
}

/**
 * @brief Checks if the given name is invalid.
 *
 * An invalid name is defined as an empty string or
 * a string that contains anything else than letters an whitespaces.
 *
 * @param name The name to be validated.
 * @return true if the name is invalid, false otherwise.
 */
bool StringUtils::IsInvalidName(const std::string &name) {
    std::regex pattern("^[a-zA-Z ]+$");
    return !(std::regex_match(name, pattern));
}