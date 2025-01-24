#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP

#include <string>

class StringUtils {
    public:

        static bool IsInvalidNickname(const std::string &nickname);

        static bool IsInvalidName(const std::string &name);
};

#endif