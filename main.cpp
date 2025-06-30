#include <iostream>
#include "cube_state.hpp"
#include "ida_star.hpp"

CubeState getSolvedCube() {
    CubeState cube;
    for (int i = 0; i < 8; ++i) {
        cube.corner_pos[i] = i;
        cube.corner_orient[i] = 0;
    }
    for (int i = 0; i < 12; ++i) {
        cube.edge_pos[i] = i;
        cube.edge_orient[i] = 0;
    }
    return cube;
}

std::string moveToStr(Move m) {
    const char* names[] = {
        "U", "U2", "U'", "D", "D2", "D'", "L", "L2", "L'",
        "R", "R2", "R'", "F", "F2", "F'", "B", "B2", "B'"
    };
    return names[m];
}

int main() {
    CubeState cube = getSolvedCube();
    cube.applyMove(F);
    cube.applyMove(R);
    cube.applyMove(U);

    std::vector<Move> solution;
    if (ida_star(cube, solution)) {
        std::cout << "Solution found in " << solution.size() << " moves:\n";
        for (Move m : solution) {
            std::cout << moveToStr(m) << " ";
        }
        std::cout << "\n";
    } else {
        std::cout << "No solution found.\n";
    }
    return 0;
}
