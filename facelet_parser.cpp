#include "facelet_parser.hpp"
#include <stdexcept>
#include <unordered_map>
#include <array>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

enum Face { U, L, F, R, B, D };

static const std::unordered_map<char, Face> color_to_face = {
    {'W', U}, {'O', L}, {'G', F},
    {'R', R}, {'B', B}, {'Y', D}
};

struct CornerRef {
    std::array<std::pair<Face, int>, 3> facelets;
};

const CornerRef corner_facelets[8] = {
    { std::array<std::pair<Face, int>, 3>{ { {U,8}, {R,0}, {F,2} } } },
    { std::array<std::pair<Face, int>, 3>{ { {U,2}, {B,0}, {R,2} } } },
    { std::array<std::pair<Face, int>, 3>{ { {U,0}, {L,0}, {B,2} } } },
    { std::array<std::pair<Face, int>, 3>{ { {U,6}, {F,0}, {L,2} } } },
    { std::array<std::pair<Face, int>, 3>{ { {D,2}, {F,8}, {R,6} } } },
    { std::array<std::pair<Face, int>, 3>{ { {D,0}, {R,8}, {B,6} } } },
    { std::array<std::pair<Face, int>, 3>{ { {D,6}, {B,8}, {L,6} } } },
    { std::array<std::pair<Face, int>, 3>{ { {D,8}, {L,8}, {F,6} } } }
};

struct EdgeRef {
    std::pair<Face, int> a, b;
};

const EdgeRef edge_facelets[12] = {
    {{U, 5}, {R, 1}}, {{U, 7}, {F, 1}}, {{U, 3}, {L, 1}}, {{U, 1}, {B, 1}},
    {{D, 5}, {R, 7}}, {{D, 7}, {F, 7}}, {{D, 3}, {L, 7}}, {{D, 1}, {B, 7}},
    {{F, 5}, {R, 3}}, {{F, 3}, {L, 5}}, {{B, 3}, {L, 3}}, {{B, 5}, {R, 5}}
};

CubeState parse_facelets(const std::string& filename) {
    CubeState cube;
    std::array<std::array<char, 9>, 6> f;
    for (auto& face : f) face.fill(' ');  // initialize with blanks

    std::ifstream infile(filename);
    if (!infile) {
        throw std::runtime_error("Could not open facelet input file.");
    }

    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        int face, pos;
        char color;
        if (!(iss >> face >> pos >> color)) {
            throw std::runtime_error("Invalid line format in input file.");
        }
        if (face < 0 || face >= 6 || pos < 0 || pos >= 9) {
            throw std::runtime_error("Invalid face or position index.");
        }
        f[face][pos] = color;
    }

    // Verify all 54 facelets are filled
    std::unordered_map<char, int> color_count;
    for (const auto& face : f) {
        for (char c : face) {
            if (c == ' ') throw std::runtime_error("Missing facelet entry.");
            color_count[c]++;
        }
    }
    for (const auto& [c, count] : color_count) {
        if (count != 9) {
            throw std::runtime_error(std::string("Color '") + c + "' appears " + std::to_string(count) + " times (expected 9).");
        }
    }

    std::array<std::array<Face, 3>, 8> corner_faces = {{
        {U, R, F}, {U, B, R}, {U, L, B}, {U, F, L},
        {D, F, R}, {D, R, B}, {D, B, L}, {D, L, F}
    }};

    for (int i = 0; i < 8; ++i) {
        auto [a, b, c] = corner_facelets[i].facelets;
        char col[3] = {f[a.first][a.second], f[b.first][b.second], f[c.first][c.second]};
        int perm = -1, orient = -1;

        for (int j = 0; j < 8; ++j) {
            auto expected = corner_faces[j];
            for (int o = 0; o < 3; ++o) {
                Face f0 = color_to_face.at(col[o]);
                Face f1 = color_to_face.at(col[(o + 1) % 3]);
                Face f2 = color_to_face.at(col[(o + 2) % 3]);

                if (f0 == expected[0] && f1 == expected[1] && f2 == expected[2]) {
                    perm = j;
                    orient = o;
                    break;
                }
            }
            if (perm != -1) break;
        }

        if (perm == -1) {
            throw std::runtime_error("Invalid corner colors (no match)");
        }

        cube.corner_pos[i] = perm;
        cube.corner_orient[i] = orient;
    }

    std::array<std::pair<Face, Face>, 12> edge_faces = {{
        {U, R}, {U, F}, {U, L}, {U, B},
        {D, R}, {D, F}, {D, L}, {D, B},
        {F, R}, {F, L}, {B, L}, {B, R}
    }};

    for (int i = 0; i < 12; ++i) {
        auto [a, b] = edge_facelets[i];
        char ca = f[a.first][a.second];
        char cb = f[b.first][b.second];

        int perm = -1, orient = -1;
        for (int j = 0; j < 12; ++j) {
            auto [fa, fb] = edge_faces[j];
            Face f0 = color_to_face.at(ca);
            Face f1 = color_to_face.at(cb);

            if (f0 == fa && f1 == fb) {
                perm = j;
                orient = 0;
                break;
            } else if (f1 == fa && f0 == fb) {
                perm = j;
                orient = 1;
                break;
            }
        }

        if (perm == -1) {
            throw std::runtime_error("Invalid edge colors (no match)");
        }

        cube.edge_pos[i] = perm;
        cube.edge_orient[i] = orient;
    }

    return cube;
}
