#ifndef GENRES_N_RATE_H
#define GENRES_N_RATE_H

#include <iostream>
#include <string>
#include <vector>

class GENRES_N_RATE {
    public:
        std::vector<std::string> genres;
        std::string maxRate;
        GENRES_N_RATE(std::vector<std::string> genres, std::string rate);
};

#endif