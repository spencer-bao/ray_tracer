#include "rt.h"
#include "obj.h"
#include "light.h"
#include "sphere.h"

#include <stdio.h>
#include <stdlib.h>

void read_objs (OBJ_T **list){ // **list points to the head to the list of spheres

    SPHERE_T sphere; // holds the values of the inputs
    COLOR_T color;
    OBJ_T *tmp;
    *list = NULL;

    // Reads spheres from stdio
    // Creates linked list using dynamic memory
    while (scanf("%lf %lf %lf %lf %lf %lf %lf", &sphere.ctr.x, &sphere.ctr.y, &sphere.ctr.z, 
                                                &sphere.radius, &color.R, &color.G, &color.B) == 7)
    {    
        tmp = (OBJ_T *) malloc(sizeof(OBJ_T));
        tmp -> sphere.ctr = sphere.ctr;
        tmp -> sphere.radius = sphere.radius;
        tmp -> color = color;

        tmp -> next = *list; // insert the new sphere object at the head of the list
        *list = tmp;        
    }
}

// Formally called cast; most code is as before, but keeps closest object pointer, closest intersection point,
// and closest normal; calls illuminate method for light and returns lighted color of closest sphere.
COLOR_T trace (RAY_T ray, OBJ_T *list, LIGHT_T light)
{

    double min_t = 10000;
    double t;
    VEC_T int_pt;
    VEC_T normal;

    OBJ_T *closest_obj = NULL;
    VEC_T closest_int_pt;
    VEC_T closest_normal;

    OBJ_T *obj;
    COLOR_T color;
    color.R = 0; color.G = 0; color.B = 0;

    for (obj = list; obj != NULL; obj = obj -> next)
    {
        if (intersect_sphere(ray, obj -> sphere, &t, &int_pt, &normal))
        {
            if (t < min_t)
            {   
                closest_obj = obj;
                closest_int_pt = int_pt;
                closest_normal = normal;

                color = obj -> color; // gets the color at the current sphere from the sph_list
                min_t = t; // sets a new closest distance of the camera and closest sphere 
            }
        }
    }

    if (closest_obj != NULL)
            color = illuminate(ray, light, list, closest_obj, closest_int_pt, closest_normal);

    return color;

}

int main(void)
{

    // calls read_objs
    // initializes image file
    OBJ_T *sph_list;
    read_objs(&sph_list);
    printf("P6\n1000 1000\n255\n"); // PPM file header

    COLOR_T color;
    color.R = 0; color.G = 0; color.B = 0;

    LIGHT_T light_source;
    light_source.loc.x = 5; light_source.loc.y = 10; light_source.loc.z = 0; // (0, 0, 10) for creative.txt

    // loops though pixels: sets ray, calls cast, prints pixel
    for (int y = 0; y < 1000; y++)
    {
        for (int x = 0; x < 1000; x++)
        {   // create a ray
            RAY_T ray;
            ray.orig.x = 0.0; ray.orig.y = 0.0; ray.orig.z = 0.0;
            ray.dir.x = -0.5 + (x/1000.0); ray.dir.y = 0.5 - (y/1000.0); ray.dir.z = 1.0;
            
            // normalize ray.dir
            ray.dir = normalize(ray.dir);

            // check for intersection
            color = trace(ray, sph_list, light_source);

            // caps color
            if (color.R > 1)
                color.R = 1;

            if (color.G > 1)
                color.G = 1;

            if (color.B > 1)
                color.B = 1;

            // write color
            printf("%c%c%c", (unsigned char) (color.R * 255), (unsigned char) (color.G * 255), 
                              (unsigned char) (color.B * 255));
        }
    }
    // frees linked list
    OBJ_T *obj;
    for (obj = sph_list; obj != NULL; obj = obj -> next)
    {
        free(obj);
    }
    
    return 0;

}