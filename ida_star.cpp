#include "ida_star.hpp"
#include "heuristic.hpp"
#include <limits>

namespace {
    bool dfs(CubeState& state, int g, int bound, int& next_bound, std::vector<Move>& path) {
        int f = g + heuristic(state);
        if (f > bound) {
            next_bound = std::min(next_bound, f);
            return false;
        }

        if (state.is_solved()) return true;

        for (int i = 0; i < 18; ++i) {
            Move m = static_cast<Move>(i);
            CubeState next = state;
            next.apply_move(m);
            path.push_back(m);
            if (dfs(next, g + 1, bound, next_bound, path)) return true;
            path.pop_back();
        }

        return false;
    }
}

bool ida_star(CubeState start, std::vector<Move>& solution) {
    int bound = heuristic(start);
    while (true) {
        int next_bound = std::numeric_limits<int>::max();
        if (dfs(start, 0, bound, next_bound, solution)) return true;
        if (next_bound == std::numeric_limits<int>::max()) return false;
        bound = next_bound;
    }
}

