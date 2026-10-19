#ifndef SCENE_H
#define SCENE_H

struct Vector3 {
  float x, y, z;
};
typedef struct Vector3 Vec3;

struct AABCube {
    Vec3 low, high;
};

struct Sphere {
    Vec3 center;
    float radius;
};

struct Scene {
    union {
        struct AABCube cube;
        struct Sphere sphere;
    } *shapes;
    int *shapetypes;
    size_t n;
};

struct Scene create_scene(size_t n);
void free_scene(struct Scene* s);
int load_scene(char* path);

#endif
