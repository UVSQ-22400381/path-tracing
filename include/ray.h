#ifndef RAY_H
#define RAY_H

#include "vec3.h"
#include "raycast.h"


typedef struct {
    Vec3 origin;
    Vec3 directions;
} Ray;
 
// Calcule la direction du rayon visant un pixel
Vec 3 ray_direction(const Camera *cam, size_t i, size_t j, size_t width, size_t height, float fov);


#endif