#pragma once
#include <array>
#include <vector>
enum class ShapeType {Empty, O, S, T, J, L, Z, I};
namespace ShapeDatabase {
    using Matrix = std::array<std::pair<int, int>, 4>;
    using TypeRotations = std::array<Matrix, 4>;
    namespace detail {
        int hash(ShapeType shape) {return static_cast<int>(shape);}
        const std::vector<TypeRotations> database = {
            {{//Empty
                {{{0,0},{0,0},{0,0},{0,0}}}, // rotation 0
                {{{0,0},{0,0},{0,0},{0,0}}}, // rotation 1
                {{{0,0},{0,0},{0,0},{0,0}}}, // rotation 2
                {{{0,0},{0,0},{0,0},{0,0}}}  // rotation 3  
            }},
            {{// O
                {{{0,0},{0,1},{1,0},{1,1}}}, // rotation 0
                {{{0,0},{0,1},{1,0},{1,1}}}, // rotation 1
                {{{0,0},{0,1},{1,0},{1,1}}}, // rotation 2
                {{{0,0},{0,1},{1,0},{1,1}}} // rotation 3
            }},
            {{// S
                {{{0,1},{0,2},{1,0},{1,1}}}, // rotation 0 (spawn)
                {{{0,1},{1,1},{1,2},{2,2}}}, // rotation 1 (90° CW)
                {{{1,1},{1,2},{2,0},{2,1}}}, // rotation 2 (180°)
                {{{0,0},{1,0},{1,1},{2,1}}}  // rotation 3 (270°)
            }},
            {{// T
                {{{0,1},{1,0},{1,1},{1,2}}}, // rotation 0 (spawn, stem up)
                {{{0,1},{1,1},{1,2},{2,1}}}, // rotation 1 (90° CW, stem right)
                {{{1,0},{1,1},{1,2},{2,1}}}, // rotation 2 (180°, stem down)
                {{{0,1},{1,0},{1,1},{2,1}}}  // rotation 3 (270° CW, stem left)
            }},
            {{// J
                {{{0,0},{1,0},{1,1},{1,2}}}, // rotation 0 (spawn)
                {{{0,1},{0,2},{1,1},{2,1}}}, // rotation 1 (90° CW)
                {{{1,0},{1,1},{1,2},{2,2}}}, // rotation 2 (180°)
                {{{0,1},{1,1},{2,0},{2,1}}}  // rotation 3 (270° CW)
            }},
                {{// L
                {{{0,2},{1,0},{1,1},{1,2}}}, // rotation 0 (spawn)
                {{{0,1},{1,1},{2,1},{2,2}}}, // rotation 1 (90° CW)
                {{{1,0},{1,1},{1,2},{2,0}}}, // rotation 2 (180°)
                {{{0,0},{0,1},{1,1},{2,1}}}  // rotation 3 (270° CW)
            }},
            {{// Z
                {{{0,0},{0,1},{1,1},{1,2}}}, // rotation 0
                {{{0,2},{1,1},{1,2},{2,1}}}, // rotation 1
                {{{1,0},{1,1},{2,1},{2,2}}}, // rotation 2 
                {{{0,1},{1,0},{1,1},{2,0}}}  // rotation 3 
            }},
            {{// I
                {{{1,0},{1,1},{1,2},{1,3}}}, // rotation 0 (horizontal, row 1)
                {{{0,2},{1,2},{2,2},{3,2}}}, // rotation 1 (vertical, col 2)
                {{{2,0},{2,1},{2,2},{2,3}}}, // rotation 2 (horizontal, row 2)
                {{{0,1},{1,1},{2,1},{3,1}}}  // rotation 3 (vertical, col 1)
            }},
        };
        const std::vector<std::array<std::pair<int, int>, 5>> jlstz_kick = {
            {{{0, 0}, {0, -1}, {1, -1}, {-2, 0}, {-2, -1}}}, // rotation 0
            {{{0, 0}, {0, 1}, {-1, 1}, {2, 0}, {2, 1}}}, // rotation 1
            {{{0, 0}, {0, 1}, {1, 1}, {-2, 0}, {-2, 1}}}, // rotation 2
            {{{0, 0}, {0, 1}, {-1, -1}, {2, 0}, {2, -1}}}  // rotation 3  
        };
        const std::vector<std::array<std::pair<int, int>, 5>> Ikick = {
            {{{0, 0}, {0, -2}, {0, 1}, {1, -2}, {-2, 1}}}, // 0->R
            {{{0, 0}, {0, -1}, {0, 2}, {-2, -1}, {1, 2}}}, // R->2
            {{{0, 0}, {0, 2}, {0, -1}, {-1, 2}, {2, -1}}}, // 2->L
            {{{0, 0}, {0, 1}, {0, -2}, {2, 1}, {-1, -2}}}  // L->0 (Tests: x+2 y+1, x-1 y-2)
        };
    }
    [[nodiscard]]static const Matrix& getMatrix(ShapeType type, int rotation) {return detail::database.at(detail::hash(type)).at(rotation);}
    [[nodiscard]]static const std::array<std::pair<int, int>, 5>& getKick(ShapeType type, int rotation) {
        if(type != ShapeType::I) 
            return detail::jlstz_kick.at(rotation);
        return detail::Ikick.at(rotation);
    }
}