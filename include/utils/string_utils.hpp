#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP

#include <string>

class StringUtils {
    public:

        /**
         * @brief Checks if the given nickname is invalid.
         *
         * An invalid nickname is defined as either an empty string or
         * a string that contains spaces.
         *
         * @param nickname The nickname to be validated.
         * @return true if the nickname is invalid, false otherwise.
         */
        static bool IsInvalidNickname(const std::string &nickname);


        /**
         * @brief Checks if the given name is invalid.
         *
         * An invalid name is defined as an empty string or
         * a string that contains anything else than letters an whitespaces.
         *
         * @param name The name to be validated.
         * @return true if the name is invalid, false otherwise.
         */
        static bool IsInvalidName(const std::string &name);
};

#endif