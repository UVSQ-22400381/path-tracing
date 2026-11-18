#include "unity.h"
#include "collision.h"
#include "scene.h"

#define EPSILON 0.0001f

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

void test_first_scene_collision_returns_closest_sphere(void)
{
    // Create two spheres aligned with the ray.
    struct Scene scene;

    struct Sphere sphere1 = {
        .center = {5.0f, 0.0f, 0.0f},
        .radius = 1.0f
    };

    struct Sphere sphere2 = {
        .center = {10.0f, 0.0f, 0.0f},
        .radius = 1.0f
    };

    union Shape shapes[2];
    shapes[0].sphere = sphere1;
    shapes[1].sphere = sphere2;

    int types[2] = {ST_SPHERE, ST_SPHERE};

    struct Color colors[2] = {{0, 0, 0}, {255, 255, 255}};

    scene.n = 2;
    scene.shapes = shapes;
    scene.shapetypes = types;
    scene.colors = colors;

    // Create a ray pointing along the positive X axis.
    Ray ray = {
        .origin = {0.0f, 0.0f, 0.0f},
        .direction = {1.0f, 0.0f, 0.0f}
    };

    // Find the first collision.
    Collision result = first_scene_collision(&ray, &scene);

    // Check that the closest sphere was selected.
    TEST_ASSERT_EQUAL_INT(0, result.object_index);

    // Check the intersection point.
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 4.0f, result.point.x);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 0.0f, result.point.y);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 0.0f, result.point.z);
}


void test_first_scene_collision_returns_box(void)
{
    // Create a scene containing one box.
    struct Scene scene;

    struct AABBox box = {
        .low = {4.0f, -1.0f, -1.0f},
        .high = {6.0f, 1.0f, 1.0f}
    };

    union Shape shapes[1];
    shapes[0].box = box;

    int types[1] = {ST_BOX};

    struct Color colors[1] = {{255, 0, 0}};

    scene.n = 1;
    scene.shapes = shapes;
    scene.shapetypes = types;
    scene.colors = colors;

    // Create a ray pointing along the positive X axis.
    Ray ray = {
        .origin = {0.0f, 0.0f, 0.0f},
        .direction = {1.0f, 0.0f, 0.0f}
    };

    // Find the first collision.
    Collision result = first_scene_collision(&ray, &scene);

    // Check that the box was selected.
    TEST_ASSERT_EQUAL_INT(0, result.object_index);

    // Check the intersection point.
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 4.0f, result.point.x);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 0.0f, result.point.y);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 0.0f, result.point.z);
}
