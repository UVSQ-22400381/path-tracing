#include "collision.h"
#include "ray.h"
#include "raycast.h"
#include "renderer.h"
#include "scene.h"
#include <stdio.h>

enum {
    SIZE = 512,
};

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <scene_path>", argv[0]);
        exit(1);
    }

    // TODO: allow user to pass render configuration through CLI
    struct Scene s      = load_scene_file(argv[1]);
    const Vec3 eye      = { -10.f, 2.5f, 2.5f };
    const Vec3 target   = { eye.x + 1.f, eye.y, eye.z };
    const Camera *cam   = new_camera(eye, target);
    const float fov     = 1.0472; // 60degs in radians

    printf("> Setting up viewport\n");
    Ray viewport[SIZE * SIZE];
    for (size_t i = 0; i < SIZE; i++) {
        for (size_t j = 0; j < SIZE; j++) {
            viewport[j * SIZE + i] = (Ray){
                .origin     = eye,
                .direction  = ray_direction(cam, i, j, SIZE, SIZE, fov),
            };
        }
    }

    printf("> Setting up image\n");
    struct Image img = new_img(SIZE, SIZE);
    for (size_t i = 0; i < SIZE; i++) {
        for (size_t j = 0; j < SIZE; j++) {
            struct Pixel *pixel = &img.pixels[j * SIZE + i];
            const Collision c = first_scene_collision(
                &viewport[j * SIZE + i],
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
