#ifndef SCENE_H
#define SCENE_H

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

struct Scene {
    union {
        struct Sphere sphere;
        struct AABBox box;
    } *shapes;
    int *shapetypes;
    size_t n;
};

int init_scene(struct Scene* sc, size_t n);
void free_scene(struct Scene* s);
int load_scene(struct Scene* s, char* path);

#endif
