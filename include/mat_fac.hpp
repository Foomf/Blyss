#pragma once

#include "matrix.hpp"

namespace mat_fac
{
    matrix<3> translate(float x, float y);

    matrix<4> orthographic(float r, float l, float t, float b, float f, float n);
}