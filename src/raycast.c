#include<stdio.h>
#include  <stdlib.h>
#include "raycast.h"

Camera* new_camera(Vec3 position){
    Camera* cam=malloc(sizeof(Camera));
    if( cam == NULL){
        perror("Erreur d'allocation");
        exit(1);
    }

    cam->position=position;
    //initialisation avec la base canonique
    cam->t=(Vec3){1.0f, 0.0f, 0.0f}; // axe x
    cam->v=(Vec3){0.0f, 1.0f, 0.0f}; // axe y
    cam->b=(Vec3){0.0f, 0.0f, 1.0f}; // axe z

    return cam;
}

void free_camera(Camera* cam){
    free(cam);
}

//rotation de la caméra autour de l'axe horiznetal z
Vec3 rotate_camera_vertical(Camera *cam, float alpha){
    Vec3 res;
    float c = cos(alpha);
    float s = sin( alpha);
    Mat3 pitch={{c,-s,0},
                {s,c,0},
                {0,0,1}}; 
    
    res.x = pitch.row[0].x * cam->t.x
          + pitch.row[0].y * cam->t.y
          + pitch.row[0].z * cam->t.z;

    res.y = pitch.row[1].x * cam->t.x
          + pitch.row[1].y * cam->t.y
          + pitch.row[1].z * cam->t.z;

    res.z = pitch.row[2].x * cam->t.x
          + pitch.row[2].y * cam->t.y
          + pitch.row[2].z * cam->t.z;

    return res;

}

//rotation de la caméra autour de l'axe vertical y
Vec3 rotate_camera_horizontal(Camera *cam, float beta){
    Vec3 res;
    float c = cos(beta);
    float s = sin( beta);
    Mat3 yaw={{c,0,s},
              {0,1,0},
              {-s,0,c}}; 
    
    res.x = yaw.row[0].x * cam->b.x
          + yaw.row[0].y * cam->b.y
          + yaw.row[0].z * cam->b.z;

    res.y = yaw.row[1].x * cam->b.x
          + yaw.row[1].y * cam->b.y
          + yaw.row[1].z * cam->b.z;

    res.z = yaw.row[2].x * cam->b.x
          + yaw.row[2].y * cam->b.y
          + yaw.row[2].z * cam->b.z;

    return res;

}
