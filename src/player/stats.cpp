#include <iostream>
#include "stats.hpp"


std::ostream& operator<<(std::ostream& os, const Stats& stats) {
    os << "Stats:" << "\n"
       << "Total Wins: " << stats.TotalWins << "\n"
       << "Wins TTT: " << stats.winsTTT << "\n"
       << "Wins Lig4: " << stats.winsLig4 << "\n"
       << "Wins Reversi: " << stats.winsReversi << "\n"
       << "Total Loses: " << stats.TotalLoses << "\n"
       << "Loses TTT: " << stats.losesTTT << "\n"
       << "Loses Lig4: " << stats.losesLig4 << "\n"
       << "Loses Reversi: " << stats.losesReversi << "\n";
    return os;
}