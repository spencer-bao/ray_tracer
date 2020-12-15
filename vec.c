#include <math.h>
#include "vec.h"

VEC_T normalize (VEC_T vec)
{
    double distance = sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
    vec.x /= distance;
    vec.y /= distance;
    vec.z /= distance;

    return vec;
}

double dot (VEC_T v1, VEC_T v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}