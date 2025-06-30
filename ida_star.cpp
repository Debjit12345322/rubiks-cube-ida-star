#include "ida_star.hpp"
#include "heuristic.hpp"
#include <climits>

int search(CubeState& node, int g, int threshold, std::vector<Move>& path, Move last_move) {
    int f = g + heuristic(node);
    if (f > threshold) return f;
    if (node.isSolved()) return -1;

    int min_next_f = INT_MAX;

    for (int m = 0; m < NUM_MOVES; ++m) {
        Move move = static_cast<Move>(m);

        if ((g > 0) && (move / 3 == last_move / 3) && ((move + last_move) % 3 == 2))
            continue;

        CubeState next = node;
        next.applyMove(move);
        path.push_back(move);
        int result = search(next, g + 1, threshold, path, move);
        if (result == -1) return -1;
        if (result < min_next_f) min_next_f = result;
        path.pop_back();
    }

    return min_next_f;
}

bool ida_star(CubeState start, std::vector<Move>& solution) {
    int threshold = heuristic(start);

    while (true) {
        std::vector<Move> path;
        int result = search(start, 0, threshold, path, static_cast<Move>(-1));
        if (result == -1) {
            solution = path;
            return true;
        }
        if (result == INT_MAX) return false;
        threshold = result;
    }
}
