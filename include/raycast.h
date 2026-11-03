#ifndef RAYCAST_H
#define RAYCAST_H
#include "vec3.h"

typedef struct {
    Vec3 position;
    float alpha;
    float beta;
    Vec3 t; // direction de visée (devant/derrière)
    Vec3 v; // direction verticale
    Vec3 b; // direction horizontale (droite/gauche)
} Camera;

Camera* new_camera(Vec3 position, Vec3 target);
void free_camera(Camera *cam);

void rotate_cam(Camera *cam);

#endif 
