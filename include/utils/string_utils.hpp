#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP

#include <string>
#include <map>
#include "exceptions.hpp"

class StringUtils {
    public:

        static bool IsInvalidNickname(const std::string &nickname);

        static bool IsInvalidName(const std::string &name);

        static std::pair<int, int> IsValidMoveInput(const std::string &row, const std::string &col);
        
        static int IsValidMoveInput(const std::string &col);
};
        
#endif