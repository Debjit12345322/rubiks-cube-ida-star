#include "cube_state.hpp"
#include "ida_star.hpp"
#include "facelet_parser.hpp"
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./rubik_solver <facelets.txt>" << std::endl;
        return 1;
    }

    std::string path = argv[1];

    try {
        CubeState scrambled = parse_facelets(path);
        std::vector<Move> solution;

        if (ida_star(scrambled, solution)) {
            std::cout << "Solution found in " << solution.size() << " moves:\n";
            for (const auto& move : solution) {
                std::cout << move_to_string(move) << " ";
            }
            std::cout << std::endl;
        } else {
            std::cout << "No solution found.\n";
        }

    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
