#include "exceptions.hpp"

/**
 * @class InexistentPlayerException
 * @brief Exception class for handling cases where a player does not exist.
 *
 * @extends std::invalid_argument
 */
InexistentPlayerException::InexistentPlayerException() : std::invalid_argument("[X] - O jogador não existe") {}

/**
 * @class PlayerNotInListException
 * @brief Exception class for handling cases where a player is not found in a list.
 *
 * @extends std::invalid_argument
 */
PlayerNotInListException::PlayerNotInListException() : std::invalid_argument("[X] - O jogador não está na lista") {}

/**
 * @class PlayerAlreadyExistsException
 * @brief Exception thrown when attempting to add a player that already exists.
 * 
 * @extends std::invalid_argument
 */
PlayerAlreadyExistsException::PlayerAlreadyExistsException() : std::invalid_argument("[X] - O jogador já está na lista") {}


/**
 * @class InvalidInputException
 * @brief Exception thrown when the input is invalid.
 * 
 * @extends std::invalid_argument
 */
InvalidInputException::InvalidInputException(const std::string &msg) : std::invalid_argument(msg) {}
