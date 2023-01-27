#ifndef ENUMI_HPP
#define ENUMI_HPP
#include <string>

enum Poravnanje {
    LEFT,
    RIGHT,
    CENTER,
    UPPER,
    LOWER
};

std::string poravnanje_to_string(Poravnanje p);

Poravnanje poravnanje_from_string(std::string s);
#endif // ENUMI_HPP
