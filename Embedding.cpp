#include "Embedding.hpp"
#include "InvalidDimensionsException.hpp"
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <iomanip>

Embedding::Embedding(char* line) {
    std::stringstream ss(line);
    std::string value;

    std::getline(ss, value, ',');
    word = value;

    while (std::getline(ss, value, ',')) {
        double dvalue = std::stod(value);
        v.push_back(dvalue);
    }
}

Embedding::Embedding(const std::string& line) {
    std::stringstream ss(line);
    std::string value;

    std::getline(ss, value, ',');
    word = value;

    while (std::getline(ss, value, ',')) {
        double dvalue = std::stod(value);
        v.push_back(dvalue);
    }
}

Embedding::Embedding(const Embedding& e) {
    word = e.getWord();
    v = e.getVector();
}

std::string Embedding::getWord() const {return word;}
std::vector<double> Embedding::getVector() const {return v;}
int Embedding::getDimensions() const {return v.size();}

Embedding& Embedding::operator=(const Embedding& e) {
    word = e.getWord();
    v = e.getVector();
    return *this;
}

Embedding Embedding::operator+(const Embedding& e) const {
    if (e.getVector().size() != getVector().size()) {
        throw InvalidDimensionsException();
    }
    Embedding result = *this;
    result.word = this->word + "+" + e.getWord();

    std::vector<double> v2 = e.getVector();
    for (size_t i = 0; i < this->v.size(); i++) {
        result.v[i] = this->v[i] + v2[i];
    }

    return result;
}

Embedding Embedding::operator-(const Embedding& e) const {
    if (e.getVector().size() != getVector().size()) {
        throw InvalidDimensionsException();
    }
    Embedding result = *this;
    result.word = this->word + "-" + e.getWord();

    std::vector<double> v2 = e.getVector();
    for (size_t i = 0; i < this->v.size(); i++) {
        result.v[i] = this->v[i] - v2[i];
    }

    return result;
}

double Embedding::operator*(const Embedding& e) const {
    double dotProduct = 0;
    double sqrtA = 0, sqrtB = 0;
    std::vector<double> v2 = e.getVector();

    for (size_t i = 0; i < this->v.size(); i++) {
        dotProduct += this->v[i] * v2[i];
    }

    for (size_t i = 0; i < this->v.size(); i++) {
        sqrtA += this->v[i] * this->v[i];
    }
    sqrtA = sqrt(sqrtA);

    for (size_t i = 0; i < this->v.size(); i++) {
        sqrtB += v2[i] * v2[i];
    }
    sqrtB = sqrt(sqrtB);

    return (dotProduct / (sqrtA * sqrtB));
}

double Embedding::operator!() const {
    double result = 0;
    for (size_t i = 0; i < this->v.size(); i++) {
        result += this->v[i] * this->v[i];
    }
    result = sqrt(result);
    return result;
}

std::ostream& operator<< (std::ostream& stream, const Embedding& e) {
    stream << "[" << e.getWord() << "] ";
    stream << std::setprecision(6) << e.getVector()[0];
    for (size_t i = 1; i < e.getVector().size(); i++) {
        stream << ", ";
        stream << std::setprecision(6) << e.getVector()[i];
    }
    stream << "\n";
    return stream;
}

