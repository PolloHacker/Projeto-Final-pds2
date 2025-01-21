#include <iostream>
#include "stats.hpp"


Stats::Stats(): TotalWins(0), winsTTT(0), winsLig4(0), winsReversi(0), TotalLoses(0), losesTTT(0), losesLig4(0), losesReversi(0) {}

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

bool Stats::operator==(const Stats& other) const {
    return TotalWins == other.TotalWins &&
            winsTTT == other.winsTTT &&
            winsLig4 == other.winsLig4 &&
            winsReversi == other.winsReversi &&
            TotalLoses == other.TotalLoses &&
            losesTTT == other.losesTTT &&
            losesLig4 == other.losesLig4 &&
            losesReversi == other.losesReversi;
}