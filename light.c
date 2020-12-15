#include "light.h"
#include <stddef.h>
#include <math.h>

// Creates light ray and iterates through objects for possible intersection; returns true if int_point is in shadow
static int shadow_test (LIGHT_T light, OBJ_T *list, OBJ_T *curr_obj, VEC_T int_pt)
{
    // compute light ray
    RAY_T L;
    L.orig = int_pt;
    L.dir.x = light.loc.x - int_pt.x; 
    L.dir.y = light.loc.y - int_pt.y; 
    L.dir.z = light.loc.z - int_pt.z;
    L.dir = normalize(L.dir);

    double a; // dummy place holders
    VEC_T b;

    OBJ_T *curr;
    for (curr = list; curr != NULL; curr = curr -> next)
    {
        if (curr != curr_obj) // check if the light ray hits any objects besides the curr obj.
        {
            if (intersect_sphere(L, curr -> sphere, &a, &b, &b))
                return 1;
        }
    }

    return 0;
}

// Computes ambient, diffuse, and specular lighting; returns final color
COLOR_T illuminate (RAY_T ray, LIGHT_T light, OBJ_T *list, OBJ_T *curr_obj, VEC_T int_pt, VEC_T normal)
{
    COLOR_T color;   
    // ambient: every part of the sphere is at least a dark shade of the color
    color.R = .1 * (curr_obj -> color.R);
    color.G = .1 * (curr_obj -> color.G);
    color.B = .1 * (curr_obj -> color.B);
    
    if (!shadow_test(light, list, curr_obj, int_pt))
    {
        VEC_T L; // the vector from the light source to where it hits the obj
        L.x = light.loc.x - int_pt.x; 
        L.y = light.loc.y - int_pt.y; 
        L.z = light.loc.z - int_pt.z;

        L = normalize(L);

        double dp = dot(L, normal);

        //diffuse, specular only if diffuse
        if (dp > 0)
        {
            color.R += dp * (curr_obj -> color.R);
            color.G += dp * (curr_obj -> color.G);
            color.B += dp * (curr_obj -> color.B);

            VEC_T R;
            R.x = L.x - (normal.x * 2 * dp);
            R.y = L.y - (normal.y * 2 * dp);
            R.z = L.z - (normal.z * 2 * dp);
            R = normalize(R);

            double dp2 = dot(R, ray.dir);

            // specular
            if (dp2 > 0)
            {
                color.R += pow(dp2, 200);
                color.G += pow(dp2, 200);
                color.B += pow(dp2, 200);
            }
        }        
    }

    return color;

}


