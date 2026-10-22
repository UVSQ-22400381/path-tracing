#ifndef RAYCAST_H
#define RAYCAST_H
#include "vec3.h"


typedef struct 
{
    Vec3 position;
    Vec3 t; //direction de la caméra
    Vec3 v; //direction vertical
    Vec3 b; //direction horizental
}Camera;

//création de la caméra
Camera* new_camera(Vec3 position);

//libération de la mémoire allouée pour la caméra
void free_camera(Camera *cam);

//rotation de la caméra autour de l'axe vertical y
Vec3 rotate_camera_vertical(Camera *cam, float beta);

//rotation de la caméra autour de l'axe horizontal z
Vec3 rotate_camera_horizontal(Camera *cam, float alpha);











#endif 
