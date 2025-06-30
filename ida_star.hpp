#pragma once
#include <vector>
#include "cube_state.hpp"
#include "move.hpp"

bool ida_star(CubeState start, std::vector<Move>& solution);
