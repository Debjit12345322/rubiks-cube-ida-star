// move.cpp
#include "move.hpp"
#include <string>

std::string move_to_string(Move move) {
    static const char* move_names[] = {
        "U", "U'", "U2",
        "D", "D'", "D2",
        "L", "L'", "L2",
        "R", "R'", "R2",
        "F", "F'", "F2",
        "B", "B'", "B2"
    };
    return move_names[static_cast<int>(move)];
}
