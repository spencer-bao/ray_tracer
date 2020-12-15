#ifndef LIGHT_H
#define LIGHT_H

#include "rt.h"
#include "obj.h"

typedef struct{
    
    VEC_T loc;

}LIGHT_T;

COLOR_T illuminate (RAY_T ray, LIGHT_T light, OBJ_T *list, OBJ_T *curr_obj, VEC_T int_pt, VEC_T normal);

#endif