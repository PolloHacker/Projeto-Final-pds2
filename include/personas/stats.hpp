#ifndef STATS_HPP
#define STATS_HPP

class Stats {

    public: 
        int TotalWins;
        int winsTTT;
        int winsLig4;
        int winsReversi;
        int TotalLoses;
        int losesTTT;
        int losesLig4;
        int losesReversi;

        Stats(): TotalWins(0), TotalLoses(0), winsTTT(0), winsLig4(0), winsReversi(0), losesTTT(0), losesLig4(0), losesReversi(0)  {}

        friend std::ostream& operator<<(std::ostream& os, const Stats& stats);

};


#endif