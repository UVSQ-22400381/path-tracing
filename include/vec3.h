#ifndef VEC3_H
#define VEC3_H
#include <math.h>

typedef struct {float x; float y; float z;} Vec3;

static inline Vec3 vec3_add(Vec3 a, Vec3 b) {
    return (Vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

static inline Vec3 vec3_sub(Vec3 a, Vec3 b) {
    return (Vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

static inline Vec3 vec3_mul(Vec3 v, float t) {
    return (Vec3){v.x * t, v.y * t, v.z * t};
}

static inline float vec3_dot(Vec3 a, Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

static inline Vec3 vec3_cross(Vec3 a, Vec3 b) {
    return (Vec3){
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

static inline float vec3_length_squared(Vec3 v) {
    return vec3_dot(v, v);
}

static inline float vec3_length(Vec3 v) {
    return sqrtf(vec3_length_squared(v));
}

static inline Vec3 vec3_normalize(Vec3 v) {
    float len = vec3_length(v);
    if (len == 0.0f) return (Vec3){0, 0, 0};
    return vec3_mul(v, 1.0f / len);
}

#endif