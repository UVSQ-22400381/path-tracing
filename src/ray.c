#include "ray.h"
#include <math.h>
#include <stddef.h>


Vec3 ray_direction(const Camera *cam, size_t i, size_t j, size_t width, size_t height, float fov) {
    
    // Viewport dimensions
    float hx = 2.0f * tanf(fov / 2.0f);
    float hy = hx * (float)(height -1) / (float)(width - 1);

    
    // Viewport center
    Vec3 center = vec3_add(cam->position, cam->t);

    // Offset between two adjacent pixels
    Vec3 qx = vec3_mul(cam->b, hx / (float)(width - 1));
    Vec3 qy = vec3_mul(cam->v, hy / (float)(height - 1));

    // Bottom-left corner of the viewport
    Vec3 p11 = vec3_sub(
        vec3_sub(center, vec3_mul(cam->b, hx / 2.0f)),
        vec3_mul(cam->v, hy / 2.0f)
    );

    // Position of the pixel using zero-based indexing
    Vec3 pixel = vec3_add(
        p11,
        vec3_add(
            vec3_mul(qx, (float)i),
            vec3_mul(qy, (float)j)
        )
    );

    // Normalize the ray direction
    return vec3_normalize(vec3_sub(pixel, cam->position));
}