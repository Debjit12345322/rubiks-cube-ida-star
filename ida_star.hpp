#pragma once
#include "cube_state.hpp"
#include "move.hpp"
#include <vector>

bool ida_star(CubeState start, std::vector<Move>& solution);
