#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

// Player Exceptions 

class InexistentPlayerException : public std::invalid_argument {
    public:
        InexistentPlayerException();
};

class PlayerNotInListException : public std::invalid_argument {
    public:
        PlayerNotInListException();
};

class PlayerAlreadyExistsException : public std::invalid_argument {
    public:
        PlayerAlreadyExistsException();
};

// Input Exceptions

class InvalidInputException : public std::invalid_argument {
    public:
        InvalidInputException(const std::string &msg);
};


#endif