#include <iostream>
#include "stats.hpp"


Stats::Stats(): TotalWins(0), winsTTT(0), winsLig4(0), winsReversi(0), TotalLoses(0), losesTTT(0), losesLig4(0), losesReversi(0) {}

std::ostream& operator<<(std::ostream& os, const Stats& stats) {
    os << "Estatisticas:" << "\n"
       << "\t- Total de vitórias: " << stats.TotalWins << "\n"
       << "\t- Vitorias Jogo da Velha: " << stats.winsTTT << "\n"
       << "\t- Vitorias Lig4: " << stats.winsLig4 << "\n"
       << "\t- Vitorias Reversi: " << stats.winsReversi << "\n"
       << "\t- Total de derrotas: " << stats.TotalLoses << "\n"
       << "\t- Derrotas Jogo da Velha: " << stats.losesTTT << "\n"
       << "\t- Derrotas Lig4: " << stats.losesLig4 << "\n"
       << "\t- Derrotas Reversi: " << stats.losesReversi << "\n";
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