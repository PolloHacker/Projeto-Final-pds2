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

/**
 * @brief Checks if the given row and column are valid.
 *
 * A valid row and column are defined as strings that contain only digits.
 *
 * @param row The row to be validated.
 * @param col The column to be validated.
 * 
 * @throws InvalidInputException if the row or column is not valid.
 */
std::pair<int, int> StringUtils::IsValidMoveInput(const std::string &row, const std::string &col) {
    std::regex pattern("^[0-9]+$");
    if (!std::regex_match(row, pattern) || !std::regex_match(col, pattern)) {
        throw InvalidInputException("[X] - Digite apenas números");
    }

    return std::make_pair(std::stoi(row), std::stoi(col));
}

/**
 * @brief Checks if the given column is valid.
 *
 * A valid column is defined as a string that contains only digits.
 *
 * @param col The column to be validated.
 * 
 * @throws InvalidInputException if the column is not valid.
 */
int StringUtils::IsValidMoveInput(const std::string &col) {
    std::regex pattern("^[0-9]+$");
    if (!std::regex_match(col, pattern)) {
        throw InvalidInputException("[X] - Digite apenas números");
    }

    return std::stoi(col);
}
