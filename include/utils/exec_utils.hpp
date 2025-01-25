#ifndef EXEC_UTILS_HPP
#define EXEC_UTILS_HPP

#include <filesystem>
#include "playerManager.hpp"
#include "TTT.hpp"
#include "lig4.hpp"
#include "reversi.hpp"

class ExecUtils {
    private:
    
        static void listFilesInDirectory(const std::string& path);
    public:

        static void PrintBanner();

        static void handleLoadPlayers(PlayerManager &pm);

        static void handleCreatePlayer(PlayerManager &pm);

        static void handleRemovePlayer(PlayerManager &pm);

        static void handleListPlayers(PlayerManager &pm);

        static void handlePlayGame(PlayerManager &pm);
};

#endif