#include "Distance.hpp"
#include "InvalidFileException.hpp"
#include <fstream>
#include <iomanip>

std::ostream& operator << (std::ostream &stream, const Distance d) {
    stream << std::setprecision(5) << d.distance << " [" << d.word << "]";
    return stream;
}

std::vector<Embedding> readVectors(std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw InvalidFileException();
    }

    std::vector<Embedding> result;
    std::string line;

    while (std::getline(file, line)) {
        Embedding e(line);       // constructor from string
        result.push_back(e);
    }

    return result;
}