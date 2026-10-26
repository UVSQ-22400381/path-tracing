#ifndef RAY_H
#define RAY_H

#include <stddef.h>
#include "vec3.h"
#include "raycast.h"

typedef struct {
    Vec3 origin;
    Vec3 direction;
} Ray;
 
// Compute the direction of the ray pointing toward a pixel.
Vec3 ray_direction(const Camera *cam, size_t i, size_t j, size_t width, size_t height, float fov);


#endif