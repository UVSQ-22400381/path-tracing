#include<stdio.h>
#include  <stdlib.h>
#include "raycast.h"

static const Vec3
T = { 1.f, 0.f, 0.f },
V = { 0.f, 1.f, 0.f },
B = { 0.f, 0.f, 1.f };

void free_camera(Camera* cam) {
    free(cam);
}

// rotation de la caméra autour de l'axe z
Vec3 pitch(float alpha, Vec3 v){
    const float c = cosf(alpha);
    const float s = sinf(alpha);

    Vec3 res = {
        .x = v.x * c - v.y * s,
        .y = v.x * s + v.y * c,
        .z = v.z,
    };

    return res;
}

// rotation de la caméra autour de l'axe y
Vec3 yaw(float beta, Vec3 v){
    const float c = cosf(beta);
    const float s = sinf(beta);
    
    Vec3 res = {
        .x = v.x * c + v.z * s,
        .y = v.y,
        .z = v.x * (-s) + v.z * c,
    };

    return res;
}

void rotate_cam(Camera *cam) {
    const float beta  = cam->beta;
    const float alpha = cam->alpha;

    cam->t = yaw(beta, pitch(alpha, T));
    cam->v = yaw(beta, pitch(alpha, V));
    cam->b = yaw(beta, pitch(alpha, B));
}

void cam_look_at(Camera *cam, Vec3 target) {
    Vec3 d = vec3_normalize(vec3_sub(target, cam->position));

    if (d.y > 0.9999f)  d.y = 0.9999f;
    if (d.y < -0.9999f) d.y = -0.9999f;

    cam->alpha = asinf(d.y);
    cam->beta  = atan2f(-d.z, d.x);

    rotate_cam(cam);
}

Camera* new_camera(Vec3 position, Vec3 target){
    Camera* cam = malloc(sizeof(Camera));
    if (cam == NULL) {
        perror("Erreur d'allocation");
        exit(1);
    }

    cam->position=position;

    cam->t = T;
    cam->v = V;
    cam->b = B;

    cam_look_at(cam, target);

    return cam;
}
