#ifndef STATS_HPP
#define STATS_HPP

#include <ostream>

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

        Stats();

        friend std::ostream& operator<<(std::ostream& os, const Stats& stats);

        

        bool operator==(const Stats& other) const;

};


#endif