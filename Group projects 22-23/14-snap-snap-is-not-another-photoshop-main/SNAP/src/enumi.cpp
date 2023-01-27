#include "../inc/enumi.hpp"

std::string poravnanje_to_string(Poravnanje p) {
    switch (p) {
        case Poravnanje::LEFT :
            return std::string("left");
        case Poravnanje::RIGHT :
             return std::string("right");
       case Poravnanje::CENTER:
            return std::string("center");
        case Poravnanje::LOWER:
            return std::string("lower");
        case Poravnanje::UPPER:
            return std::string("upper");
    }
}

Poravnanje poravnanje_from_string(std::string s) {
    if(s == "center")
        return Poravnanje::CENTER;
    else if(s == "left")
        return Poravnanje::LEFT;
    else if(s == "right")
        return Poravnanje::RIGHT;
    else if(s == "lower")
        return Poravnanje::LOWER;
    else if(s == "upper")
        return Poravnanje::UPPER;


}
