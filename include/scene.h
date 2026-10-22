#ifndef SCENE_H
#define SCENE_H

#include <stdlib.h>
#include <stdio.h>

enum shapetype {
    ST_SPHERE,
    ST_BOX,
};

struct Vector3 {
  float x, y, z;
};
typedef struct Vector3 Vec3;

struct AABBox {
    Vec3 low, high;
};

struct Sphere {
    Vec3 center;
    float radius;
};

union Shape {
    struct AABBox box;
    struct Sphere sphere;
};

struct Scene {
    size_t n;
    union Shape *shapes;
    int *shapetypes;
};

struct Scene load_scene_file(char* path);
void free_scene(struct Scene* s);

#endif
