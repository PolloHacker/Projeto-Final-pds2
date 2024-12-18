#ifndef STATS_HPP
#define STATS_HPP

struct Stats
{
    int wins;
    int loses;
    float winRate;


    Stats(): wins(0), loses(0), winRate(0) {}

    float calcWinRate() {
        return (this->wins / (this->loses + this->wins)) * 100;
    }
};


#endif