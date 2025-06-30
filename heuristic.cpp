#include "heuristic.hpp"

int heuristic(const CubeState& cube) {
    int score = 0;
    for (auto c : cube.corner_orient) if (c != 0) ++score;
    for (auto e : cube.edge_orient) if (e != 0) ++score;
    return score;
}
