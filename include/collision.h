#ifndef COLLISION_H
#define COLLISION_H

#include "vec3.h"
#include "scene.h"
#include "ray.h"

float ray_sphere_intersection(const Ray *ray, const struct Sphere *sphere);

float ray_aabb_intersection(const Ray *ray, const struct AABBox *box);



#endif