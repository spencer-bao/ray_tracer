#ifndef VEC_H
#define VEC_H

typedef struct
{
    double x;
    double y;
    double z;
} VEC_T;

VEC_T normalize (VEC_T vec);

double dot (VEC_T v1, VEC_T v2);

#endif