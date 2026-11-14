#ifndef COLLISION_H
#define COLLISION_H

#include "vec3.h"
#include "scene.h"
#include "ray.h"

Vec3 ray_sphere_intersection(const Ray *ray, const struct Sphere *sphere);

Vec3 ray_box_intersection(const Ray *ray, const struct AABBox *box);



#endif