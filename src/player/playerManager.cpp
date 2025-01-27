#include "playerManager.hpp"

/**
 * @brief Constructs a new PlayerManager object.
 * 
 * Initializes the players vector and sets the number of players to zero.
 */
PlayerManager::PlayerManager() {
    this->players = std::vector<Player>();
    this->num_players = 0;
}

/**
 * @brief Loads player data from a file and adds players to the manager.
 *
 * @param filename The path to the file containing player data.
 *
 * The function handles the following:
 * 
 * - Opens the file and checks for errors.
 * 
 * - Skips the header line.
 * 
 * - Reads each line of player data and parses it.
 * 
 * - Converts string data to appropriate types for player statistics.
 * 
 * - Adds each player to the PlayerManager.
 * 
 * - Handles exceptions for players that already exist.
 *
 * @note If there is an error opening the file, an error message is printed
 *       to the standard error stream.
 * @note If there is an error parsing a line, an error message is printed
 *       to the standard error stream.
 */
void PlayerManager::loadPlayers(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Erro ao abrir arquivo no caminho ./saves/save.csv");
    }

    std::string line;
    // Skip the header line
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        PlayerData data;

        if (this->readPlayerFromFile(ss, data)) {

            Stats stats;
            stats.TotalWins = std::stoi(data.totalWins);
            stats.winsTTT = std::stoi(data.winsTTT);
            stats.winsLig4 = std::stoi(data.winsLig4);
            stats.winsReversi = std::stoi(data.winsReversi);
            stats.TotalLoses = std::stoi(data.totalLoses);
            stats.losesTTT = std::stoi(data.losesTTT);
            stats.losesLig4 = std::stoi(data.losesLig4);
            stats.losesReversi = std::stoi(data.losesReversi);

            try {
                this->addPlayer(data.name, data.nickname, stats);
            } catch (PlayerAlreadyExistsException &e) {
                std::cerr << "Error adding player: " << e.what() << std::endl;
            }
        } else {
            std::cerr << "Error parsing line: " << line << std::endl;
        }
    }

    file.close();
}

/**
 * @brief Reads player data from a given input stream.
 * 
 * @param ss The input stream containing player data.
 * @param data The PlayerData structure to be populated with the read values.
 * @return true if both basic fields and stats fields are successfully read, 
 *         false otherwise.
 */
bool PlayerManager::readPlayerFromFile(std::istringstream &ss, PlayerData &data) {
    return this->readBasicFields(ss, data) && this->readStatsFields(ss, data);
}

/**
 * @brief Reads basic fields (id, name, and nickname) from a given input stream.
 * 
 * @param ss The input stream containing the player data.
 * @param data The PlayerData object where the read fields will be stored.
 * @return true if all fields are successfully read, false otherwise.
 */
bool PlayerManager::readBasicFields(std::istringstream &ss, PlayerData &data) {
    return this->readField(ss, data.id) && this->readField(ss, data.name) && this->readField(ss, data.nickname);
}

/**
 * @brief Reads the statistics fields from the input stream and populates the PlayerData structure.
 *
 * @param ss The input string stream containing the statistics data.
 * @param data The PlayerData structure to be populated with the read statistics.
 * @return true if all fields were successfully read and assigned; false otherwise.
 */
bool PlayerManager::readStatsFields(std::istringstream &ss, PlayerData &data) {
    return this->readField(ss, data.totalWins) && this->readField(ss, data.winsTTT) && this->readField(ss, data.winsLig4) &&
           this->readField(ss, data.winsReversi) && this->readField(ss, data.totalLoses) && this->readField(ss, data.losesTTT) &&
           this->readField(ss, data.losesLig4) && this->readField(ss, data.losesReversi);
}

/**
 * @brief Reads a field from a given input string stream.
 *
 * @param ss The input string stream to read from.
 * @param field The string reference where the read field will be stored.
 * @return true if a field was successfully read, false otherwise.
 */
bool PlayerManager::readField(std::istringstream &ss, std::string &field) {
    if (std::getline(ss, field, ',')) {
        return true;
    }
    return false;
}

/**
 * @brief Removes a player from the player list by their nickname.
 *
 * @param nickname The nickname of the player to be removed.
 * @throws InexistentPlayerException if the player with the given nickname is not found in the list.
 */
void PlayerManager::removePlayer(const std::string &nickname) {
    try {
        this->players.erase(this->getPlayer(nickname));
        this->num_players--;
    } catch (PlayerNotInListException &e) {
        throw InexistentPlayerException();
    }
}

/**
 * @brief Adds a new player to the player manager.
 * 
 * @param name The name of the player.
 * @param nickname The nickname of the player.
 * @param stats The stats of the player.
 * 
 * @throws InvalidInputException if the name or nickname is invalid.
 * @throws PlayerAlreadyExistsException if a player with the same nickname already exists.
 */
void PlayerManager::addPlayer(const std::string &name, const std::string &nickname, Stats stats) {
    if (StringUtils::IsInvalidNickname(nickname) || StringUtils::IsInvalidName(name)) {
        throw InvalidInputException("[X] - Nome ou apelido invalido");
    }
    try {
        this->getPlayer(nickname);
        throw PlayerAlreadyExistsException();
    } catch (PlayerNotInListException &e) {
        this->players.emplace_back(this->num_players++, name, nickname, stats);
    }
}

/**
 * @brief Adds a player to the PlayerManager.
 * 
 * @param name The name of the player.
 * @param nickname The nickname of the player.
 * 
 * @throws PlayerAlreadyExistsException if a player with the same name and nickname already exists.
 */
void PlayerManager::addPlayer(const std::string &name, const std::string &nickname) {
    try {
        this->addPlayer(name, nickname, Stats());
    } catch (PlayerAlreadyExistsException &e) {
        throw;    
    }
}

/**
 * @brief Retrieves an iterator to a player with the specified nickname.
 * 
 * @param nickname The nickname of the player to search for.
 * @return ```std::vector<Player>::iterator``` An iterator pointing to the player with the specified nickname.
 * @throws PlayerNotInListException If no player with the specified nickname is found.
 */
std::vector<Player>::iterator PlayerManager::getPlayer(const std::string &nickname) {
    auto player =  std::find_if(this->players.begin(), this->players.end(), 
        [nickname](const Player &el) {
            return el.getNickname() == nickname; 
        }
    );

    if (player == this->players.end()) {
        throw PlayerNotInListException();
    }
    return player;
}

/**
 * @brief Updates the statistics of a player based on the game result.
 * 
 * @param nickname The nickname of the player whose statistics are to be updated.
 * @param result The result of the game ('W' for win, 'L' for loss, etc.).
 */
void PlayerManager::updatePlayerStats(const std::string &nickname, char result) {
    Player &player = *this->getPlayer(nickname);
    player.updateStats(result, 'T');
}

/**
 * @brief Exports player data to a CSV file.
 *
 * This function creates and writes player data to a CSV file located at "./saves/save.csv".
 * The CSV file contains the following columns:
 * - Id: Player's unique identifier
 * - Name: Player's name
 * - Nickname: Player's nickname
 * - TotalWins: Total number of wins
 * - WinsTTT: Number of wins in Tic-Tac-Toe
 * - WinsLig4: Number of wins in Connect Four
 * - WinsReversi: Number of wins in Reversi
 * - TotalLoses: Total number of losses
 * - LosesTTT: Number of losses in Tic-Tac-Toe
 * - LosesLig4: Number of losses in Connect Four
 * - LosesReversi: Number of losses in Reversi
 *
 * @throws std::runtime_error if the file cannot be opened.
 */
void PlayerManager::exportPlayerData() {
    std::ofstream file("./saves/save.csv");
    if (!file.is_open()) {
        throw std::runtime_error("Erro ao abrir arquivo no caminho ./saves/save.csv");
    }

    file << "Id,Name,Nickname,TotalWins,WinsTTT,WinsLig4,WinsReversi,TotalLoses,LosesTTT,LosesLig4,LosesReversi" << std::endl;
    for (auto &player : this->players) {
        file << player.getId() << "," << player.getName() << "," << player.getNickname() << ","
             << player.getStats().TotalWins << "," << player.getStats().winsTTT << "," << player.getStats().winsLig4 << ","
             << player.getStats().winsReversi << "," << player.getStats().TotalLoses << "," << player.getStats().losesTTT << ","
             << player.getStats().losesLig4 << "," << player.getStats().losesReversi << std::endl;
    }

}

/**
 * @brief Prints a formatted table of player information.
 * 
 * This function prints a table with the following columns:
 * - Id: The player's unique identifier.
 * - Apelido: The player's nickname.
 * - Nome: The player's name.
 * - Total de vitorias: The total number of victories the player has achieved.
 * - Total de derrotas: The total number of defeats the player has suffered.
 * 
 * The column widths are dynamically adjusted based on the maximum lengths of 
 * the player names and nicknames to ensure proper alignment.
 */
void PlayerManager::printTable() {
    std::string sorter = "";
    std::cout << "Digite o tipo de ordenação (N - nome, A - apelido, I - id): ";
    std::cin >> sorter;

    size_t maxNameLength = this->getMaxNameLength() + 1;
    size_t maxNicknameLength = this->getMaxNicknameLength() + 1;

    std::vector<Player> toPrint = this->players;

    while (sorter != "N" && sorter != "A" && sorter != "I") {
        std::cout << "Digite o tipo de ordenação (N - nome, A - apelido, I - id): ";
        std::cin >> sorter;
    }
    if (sorter == "I") {
        std::sort(toPrint.begin(), toPrint.end(), [](const Player &a, const Player &b) {
            return a.getId() < b.getId();
        });
    } else if (sorter == "N") {
        std::sort(toPrint.begin(), toPrint.end(), [](const Player &a, const Player &b) {
            return a.getName() < b.getName();
        });
    } else if (sorter == "A") {
        std::sort(toPrint.begin(), toPrint.end(), [](const Player &a, const Player &b) {
            return a.getNickname() < b.getNickname();
        });
    }

    std::cout << (sorter == "I" ? "Id" : "") << std::setw(maxNicknameLength)
        << "Apelido" <<  std::setw(maxNameLength)
        << "Nome" <<  std::setw(18)
        << "Total de vitorias" << std::setw(18) << "Total de derrotas" << std::endl;

    for (auto &player : toPrint) {
        std::cout  << std::setw(2)
                  << (sorter == "I" ? std::to_string(player.getId()) : "") << std::setw(maxNicknameLength) 
                  << player.getNickname() << std::setw(maxNameLength) 
                  << player.getName() << std::setw(18) 
                  << player.getStats().TotalWins << std::setw(18)
                  << player.getStats().TotalLoses << std::endl;
    }
}

/**
 * @brief Prints the player information based on the provided nickname.
 *
 * @param nickname The nickname of the player to be printed.
 * @throws InexistentPlayerException if the player with the given nickname does not exist.
 */
void PlayerManager::printPlayerByNickname(const std::string &nickname) {
    auto player = this->getPlayer(nickname);
    if (player != this->players.end()) {
        std::cout << *player;
    } else {
        throw InexistentPlayerException();
    }
}


/**
 * @brief Prints the player information by name.
 * 
 * @param name The name of the player to search for.
 * 
 * @throws InexistentPlayerException if the player with the given name does not exist.
 */
void PlayerManager::printPlayerByName(const std::string &name) {
    auto player = std::find_if(this->players.begin(), this->players.end(), 
        [name](const Player &el) {
            return el.getName() == name; 
        }
    );

    if (player != this->players.end()) {
        std::cout << *player;
    } else {
        throw InexistentPlayerException();
    }
}

/**
 * @brief Get the current number of players.
 * 
 * @return int The number of players.
 */
int PlayerManager::getPlayerCount() {
    return PlayerManager::num_players;
}


/**
 * @brief Get the maximum length of player names.
 * 
 * @return size_t The length of the longest player name.
 */
size_t PlayerManager::getMaxNameLength() {
    size_t max = 0;
    for (auto &player : this->players) {
        if (player.getName().length() > max) {
            max = player.getName().length();
        }
    }
    return max;
}

/**
 * @brief Get the maximum length of nicknames among all players.
 * 
 * @return size_t The length of the longest nickname.
 */
size_t PlayerManager::getMaxNicknameLength() {
    size_t max = 0;
    for (auto &player : this->players) {
        if (player.getNickname().length() > max) {
            max = player.getNickname().length();
        }
    }
    return max;
}

/**
 * @brief Destructor for the PlayerManager class.
 */
PlayerManager::~PlayerManager() {
    this->players.clear();
}



/*
CADASTRO:
CJ <Apelido> <Nome> (obs. Considere que <Apelido> é composto por uma única palavra)
Jogador <Apelido> cadastrado com sucesso
ERRO: dados incorretos
ERRO: jogador repetido

REMOVER:
RJ <Apelido>
Jogador <Apelido> removido com sucesso
ERRO: jogador inexistente

LISTAGEM:
LJ [A|N]
<Apelido> <Nome>
REVERSI - V: <#vitorias> D: <#derrotas>
LIG4 - V: <#vitorias> D: <#derrotas>
VELHA - V: <#vitorias> D: <#derrotas>
*/