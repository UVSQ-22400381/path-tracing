#include<stdio.h>
#include  <stdlib.h>
#include "raycast.h"

Camera new_camera(Vec3 position, Vec3 t, Vec3 v, Vec3 b){
    Camera* cam=malloc(sizeof(Camera));
    if( cam == NULL){
        perror("Erreur d'allocation");
        return EXIT_FAILURE;
    }
}

void free_camera(Camera* cam){
    free(cam);
}

void rotate_camera_vertical(Camera *cam, float beta){


}

//rotation de la caméra autour de l'axe horizontal z
void rotate_camera_horizontal(Camera *cam, float alpha){
    

}


