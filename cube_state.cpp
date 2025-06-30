#include "cube_state.hpp"
#include "move_tables.hpp"

bool CubeState::isSolved() const {
    for (int i = 0; i < 8; i++)
        if (corner_pos[i] != i || corner_orient[i] != 0) return false;
    for (int i = 0; i < 12; i++)
        if (edge_pos[i] != i || edge_orient[i] != 0) return false;
    return true;
}

void CubeState::applyMoveEffect(const MoveEffect& effect) {
    CubeState new_state = *this;
    for (int i = 0; i < effect.corner_pos.size(); ++i) {
        int from = effect.corner_pos[(i + 1) % 4];
        int to = effect.corner_pos[i];
        new_state.corner_pos[to] = corner_pos[from];
        new_state.corner_orient[to] = (corner_orient[from] + effect.corner_rot[i]) % 3;
    }
    for (int i = 0; i < effect.edge_pos.size(); ++i) {
        int from = effect.edge_pos[(i + 1) % 4];
        int to = effect.edge_pos[i];
        new_state.edge_pos[to] = edge_pos[from];
        new_state.edge_orient[to] = (edge_orient[from] + effect.edge_rot[i]) % 2;
    }
    *this = new_state;
}

void CubeState::applyMove(Move move) {
    switch (move) {
        case U: applyMoveEffect(move_U); break;
        case U2: applyMove(U); applyMove(U); break;
        case U_PRIME: applyMove(U); applyMove(U); applyMove(U); break;

        case D: applyMoveEffect(move_D); break;
        case D2: applyMove(D); applyMove(D); break;
        case D_PRIME: applyMove(D); applyMove(D); applyMove(D); break;

        case L: applyMoveEffect(move_L); break;
        case L2: applyMove(L); applyMove(L); break;
        case L_PRIME: applyMove(L); applyMove(L); applyMove(L); break;

        case R: applyMoveEffect(move_R); break;
        case R2: applyMove(R); applyMove(R); break;
        case R_PRIME: applyMove(R); applyMove(R); applyMove(R); break;

        case F: applyMoveEffect(move_F); break;
        case F2: applyMove(F); applyMove(F); break;
        case F_PRIME: applyMove(F); applyMove(F); applyMove(F); break;

        case B: applyMoveEffect(move_B); break;
        case B2: applyMove(B); applyMove(B); break;
        case B_PRIME: applyMove(B); applyMove(B); applyMove(B); break;
    }
}
