#pragma once
#include <array>
#include "move.hpp"

struct CubeState {
    std::array<uint8_t, 8> corner_pos;
    std::array<uint8_t, 8> corner_orient;
    std::array<uint8_t, 12> edge_pos;
    std::array<uint8_t, 12> edge_orient;

    bool is_solved() const;
    void apply_move(Move move);
};
