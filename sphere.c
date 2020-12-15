#include "sphere.h"
#include "rt.h"

#include <math.h>

int intersect_sphere (RAY_T ray, SPHERE_T sphere, double *t, VEC_T *int_pt, VEC_T *normal)
{
    double A = 1.0;

    double B = 2 * (ray.dir.x * (ray.orig.x - sphere.ctr.x) + 
                    ray.dir.y * (ray.orig.y - sphere.ctr.y) +
                    ray.dir.z * (ray.orig.z - sphere.ctr.z));

    double C = pow((ray.orig.x - sphere.ctr.x), 2) + 
               pow((ray.orig.y - sphere.ctr.y), 2) + 
               pow((ray.orig.z - sphere.ctr.z), 2) - 
                (sphere.radius * sphere.radius);
    

    double discriminant = (B * B) - (4*A*C);
    
    if (discriminant < 0)
    {
       return 0;
    }

    double t1 = (-B + sqrt(discriminant)) / (2*A);
    double t2 = (-B - sqrt(discriminant)) / (2*A);

    if (t1 < 0 || t2 < 0)
    {
        return 0;
    } 
    else if (t1 < t2)
    {
        *t = t1;
    } 
    else
    {
        *t = t2;
    }

    // computes the intersection point
    (*int_pt).x = ray.orig.x + (ray.dir.x * *t); 
    (*int_pt).y = ray.orig.y + (ray.dir.y * *t);
    (*int_pt).z = ray.orig.z + (ray.dir.z * *t);

    // computes the normal vector
    (*normal).x = ((*int_pt).x - sphere.ctr.x) / sphere.radius;
    (*normal).y = ((*int_pt).y - sphere.ctr.y) / sphere.radius;
    (*normal).z = ((*int_pt).z - sphere.ctr.z) / sphere.radius;
    *normal = normalize(*normal);

    return 1;
}