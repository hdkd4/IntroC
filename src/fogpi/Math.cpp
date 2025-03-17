#include "Math.hpp"
#include "fogpi.hpp"
#include <stdio.h>
#include <math.h>

void Print(const Vector2D &_v)
{
    printf("{%f, %f}\n", _v.x, _v.y);
}

float Distance2D(const Vector2D &_v1, const Vector2D &_v2)
{
    return sqrt(powf(_v2.x - _v1.x, 2.0f) + powf(_v2.y - _v1.y, 2.0f));
}