#ifndef DISTANCE_HPP
#define DISTANCE_HPP

#include <string>
#include <vector>
#include "Embedding.hpp"

struct Distance {
    double distance;
    std::string word;

    bool operator < (const Distance& d) const {return distance < d.distance;}
};

std::ostream& operator << (std::ostream &stream, const Distance d);
std::vector<Embedding> readVectors(std::string filename);

#endif