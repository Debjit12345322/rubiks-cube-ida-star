#pragma once
#include <vector>

struct MoveEffect {
    std::vector<int> corner_pos;
    std::vector<int> corner_rot;
    std::vector<int> edge_pos;
    std::vector<int> edge_rot;
};

inline const MoveEffect move_U = {
    {3, 0, 1, 2}, {0, 0, 0, 0},
    {3, 0, 1, 2}, {0, 0, 0, 0}
};

inline const MoveEffect move_D = {
    {4, 5, 6, 7}, {0, 0, 0, 0},
    {4, 5, 6, 7}, {0, 0, 0, 0}
};

inline const MoveEffect move_L = {
    {1, 2, 6, 5}, {1, 2, 1, 2},
    {2, 10, 6, 9}, {0, 0, 0, 0}
};

inline const MoveEffect move_R = {
    {0, 4, 7, 3}, {1, 2, 1, 2},
    {0, 8, 4, 11}, {0, 0, 0, 0}
};

inline const MoveEffect move_F = {
    {0, 1, 5, 4}, {2, 1, 2, 1},
    {1, 9, 5, 8}, {1, 1, 1, 1}
};

inline const MoveEffect move_B = {
    {2, 3, 7, 6}, {2, 1, 2, 1},
    {3, 11, 7, 10}, {1, 1, 1, 1}
};
