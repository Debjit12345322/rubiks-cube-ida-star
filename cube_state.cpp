#include "cube_state.hpp"

bool CubeState::is_solved() const {
    for (int i = 0; i < 8; ++i)
        if (corner_pos[i] != i || corner_orient[i] != 0) return false;
    for (int i = 0; i < 12; ++i)
        if (edge_pos[i] != i || edge_orient[i] != 0) return false;
    return true;
}

void CubeState::apply_move(Move move) {
    // Apply predefined permutations for each move
    // Omitted here: implement based on your move tables
}

