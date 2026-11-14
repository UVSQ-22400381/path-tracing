#include "unity.h"
#include "collision.h"
#include "scene.h"

/** Tests the intersection of a ray with a sphere. */
void test_ray_sphere_intersection(void) {
    // Define a ray
    Ray ray;
    ray.origin = (Vec3){0.0f, 0.0f, 0.0f};
    ray.direction = (Vec3){1.0f, 0.0f, 0.0f};

    // Define a sphere
    struct Sphere sphere;
    sphere.center = (Vec3){5.0f, 0.0f, 0.0f};
    sphere.radius = 1.0f;

    // Calculate intersection
    Vec3 collision = ray_sphere_intersection(&ray, &sphere);

    // Check if the intersection is correct
    TEST_ASSERT_FALSE(isnan(collision.x));

    TEST_ASSERT_FLOAT_WITHIN(1e-5, 4.0f, collision.x);
    TEST_ASSERT_FLOAT_WITHIN(1e-5, 0.0f, collision.y);
    TEST_ASSERT_FLOAT_WITHIN(1e-5, 0.0f, collision.z);
}

void test_ray_box_intersection(void) {
    // Define a ray
    Ray ray;
    ray.origin = (Vec3){0.0f, 0.0f, 0.0f};
    ray.direction = (Vec3){1.0f, 0.0f, 0.0f};

    // Define a box
    struct AABBox box;
    box.low = (Vec3){4.0f, -1.0f, -1.0f};
    box.high = (Vec3){6.0f, 1.0f, 1.0f};

    // Calculate intersection
    Vec3 collision = ray_box_intersection(&ray, &box);

    // Check if the intersection is correct
    TEST_ASSERT_FALSE(isnan(collision.x));

    TEST_ASSERT_FLOAT_WITHIN(1e-5, 4.0f, collision.x);
    TEST_ASSERT_FLOAT_WITHIN(1e-5, 0.0f, collision.y);
    TEST_ASSERT_FLOAT_WITHIN(1e-5, 0.0f, collision.z);
}