#pragma once
#include <array>
#include "move.hpp"

struct MoveEffect;

struct CubeState {
    std::array<uint8_t, 8> corner_pos;
    std::array<uint8_t, 8> corner_orient;
    std::array<uint8_t, 12> edge_pos;
    std::array<uint8_t, 12> edge_orient;

    void applyMove(Move move);
    void applyMoveEffect(const MoveEffect& effect);
    bool isSolved() const;
};
