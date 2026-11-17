#ifndef COLLISION_H
#define COLLISION_H

#include "vec3.h"
#include "scene.h"
#include "ray.h"


typedef struct {
    int object_index;
    Vec3 point;
} Collision;

Vec3 ray_sphere_intersection(const Ray *ray, const struct Sphere *sphere);

Vec3 ray_box_intersection(const Ray *ray, const struct AABBox *box);

Collision first_scene_collision(Vec3 eye, const Ray *ray, const struct Scene *scene);

#endif