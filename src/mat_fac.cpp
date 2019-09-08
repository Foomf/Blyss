#include "mat_fac.hpp"

namespace mat_fac
{
    matrix<4> orthographic(float r, float l, float t, float b, float f, float n)
    {
        float orthographic[4][4] = {
            { 2 / (r - l), 0, 0, -(r + l) / (r - l) },
            { 0, 2 / (t - b), 0, -(t + b) / (t - b) },
            { 0, 0, -2 / (f - n), -(f + n) / (f - n) },
            { 0, 0, 0, 1 }
        };
        return matrix<4>(orthographic);
    }
}