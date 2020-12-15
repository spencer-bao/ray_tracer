#ifndef SPHERE_H
#define SPHERE_H

#include "vec.h"
#include "rt.h"

typedef struct
{
    VEC_T ctr;
    double radius;
} SPHERE_T;

int intersect_sphere (RAY_T ray, SPHERE_T sphere, double *t, VEC_T *int_pt, VEC_T *normal);

#endif