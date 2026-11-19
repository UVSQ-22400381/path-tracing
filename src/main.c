#include "collision.h"
#include "ray.h"
#include "raycast.h"
#include "renderer.h"
#include "scene.h"
#include "config.h"
#include <stdio.h>

#ifndef PI
#define PI 3.14159265358979323846
#endif

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <scene_path>", argv[0]);
        exit(1);
    }

    struct Scene s = load_scene_file(argv[1]);
    RenderConfig rc = init_config();
    
    const Vec3 eye      = rc.cam_pos;
    const Vec3 target   = vec3_add(eye, rc.target);
    const Camera *cam   = new_camera(eye, target);
    const float fov     = rc.fov * (PI / 180.0);

    const size_t width = rc.width;
    const size_t height = rc.height;

    printf("> Setting up viewport\n");
    Ray viewport[width * height];
    for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
            viewport[j * width + i] = (Ray){
                .origin     = eye,
                .direction  = ray_direction(cam, i, j, width, height, fov),
            };
        }
    }

    printf("> Setting up image\n");
    struct Image img = new_img(width, height);
    for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
            struct Pixel *pixel = &img.pixels[(width - 1 - j) * width + i];
            const Collision c = first_scene_collision(
                &viewport[j * width + i],
                &s
            );
            const struct Color col = s.colors[c.object_index];
            pixel->r = col.r;
            pixel->g = col.g;
            pixel->b = col.b;
        }
    }

    printf("> Writing image to './cornell_render.ppm'\n");
    save_img_ascii(&img, "./render.ppm");

    printf("> Cleaning up and closing program\n");
    free_image(&img);
    free_scene(&s);
    return 0;
}
