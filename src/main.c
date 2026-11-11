#include <stdio.h>
#include <math.h>
#include "renderer.h"
#include "raycast.h"
#include "ray.h"
#include "scene.h"
#include "collision.h"

#define WIDTH  400
#define HEIGHT 300
#define FOV    (60.0f * (float)M_PI / 180.0f)

#define D_MIN 3.0f
#define D_MAX 12.0f

static float clamp01(float x) {
    if (x < 0.0f) return 0.0f;
    if (x > 1.0f) return 1.0f;
    return x;
}

static float closest_hit(const struct Scene *scene, const Ray *r) {
    float closest = -1.0f;
    for (size_t k = 0; k < scene->n; k++) {
        float t = -1.0f;
        if (scene->shapetypes[k] == ST_SPHERE) {
            t = ray_sphere_intersection(r, &scene->shapes[k].sphere);
        }
        
        if (t > 0.0f && (closest < 0.0f || t < closest)) {
            closest = t;
        }
    }
    return closest;
}

int main(void) {
    
    Camera *cam = new_camera((Vec3){0.0f, 0.0f, 0.0f}, (Vec3){1.0f, 0.0f, 0.0f});

    
    union Shape shapes[3];
    shapes[0].sphere = (struct Sphere){ .center = {5.0f,  0.0f,  0.0f}, .radius = 1.0f };
    shapes[1].sphere = (struct Sphere){ .center = {8.0f,  0.0f,  2.5f}, .radius = 1.0f };
    shapes[2].sphere = (struct Sphere){ .center = {11.0f, 0.5f, -3.0f}, .radius = 1.5f };
    int types[3] = { ST_SPHERE, ST_SPHERE, ST_SPHERE };
    struct Scene scene = { .n = 3, .shapes = shapes, .shapetypes = types };

    struct Image img = new_img(WIDTH, HEIGHT);

    for (size_t j = 0; j < HEIGHT; j++) {
        for (size_t i = 0; i < WIDTH; i++) {
            Ray r = {
                .origin = cam->position,
                .direction = ray_direction(cam, i, j, WIDTH, HEIGHT, FOV),
            };

            byte gray = 0;
            float t = closest_hit(&scene, &r);
            if (t > 0.0f) {
                float v = 1.0f - (t - D_MIN) / (D_MAX - D_MIN);
                gray = (byte)(clamp01(v) * 255.0f);
            }

            size_t row = HEIGHT - 1 - j;
            img.pixels[row * WIDTH + i] = (struct Pixel){gray, gray, gray};
        }
    }

    if (save_img_ascii(&img, "depth.ppm") != 0)
        fprintf(stderr, "Error: could not write depth.ppm\n");
    else
        printf("Image written: depth.ppm\n");

    free_image(&img);
    free_camera(cam);
    return 0;
}