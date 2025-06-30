#pragma once
#include <string>

enum class Move {
    U, U2, U_PRIME,
    D, D2, D_PRIME,
    F, F2, F_PRIME,
    B, B2, B_PRIME,
    L, L2, L_PRIME,
    R, R2, R_PRIME
};

std::string move_to_string(Move m);
