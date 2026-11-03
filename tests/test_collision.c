#include "unity.h"
#include "collision.h"
#include "scene.h"
#include "vec.h"

void test_ray_sphere_intersection(void) {
    // Define a ray
    Ray ray;
    ray.origin = (Vec3){0.0f, 0.0f, 0.0f};
    ray.direction = (Vec3){1.0f, 0.0f, 0.0f};

    // Define a sphere that the ray will intersect
    struct Sphere sphere;
    sphere.center = (Vec3){5.0f, 0.0f, 0.0f};
    sphere.radius = 1.0f;

    // Calculate intersection
    float t = ray_sphere_intersection(&ray, &sphere);

    // Check if the intersection is correct
    TEST_ASSERT(t > 0); // There should be an intersection
    TEST_ASSERT_FLOAT_WITHIN(1e-5, 4.0f, t); // The intersection point should be at t=4
}