#ifndef RT_H
#define RT_H

#include "vec.h"

typedef struct{

    VEC_T orig;
    VEC_T dir;

} RAY_T;

typedef struct{

    double R;
    double G;
    double B;

} COLOR_T;



#endif