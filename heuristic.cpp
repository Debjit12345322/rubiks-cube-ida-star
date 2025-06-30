#include "heuristic.hpp"

int heuristic(const CubeState& cube) {
    int corner_twist = 0;
    for (int c : cube.corner_orient) {
        if (c != 0) {
            corner_twist = 1;
            break;
        }
    }

    int edge_flip = 0;
    for (int e : cube.edge_orient) {
        if (e != 0) {
            edge_flip = 1;
            break;
        }
    }

    return corner_twist + edge_flip;
}
