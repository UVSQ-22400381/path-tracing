#include "unity.h"

extern void test_img_alloc(void);
extern void test_img_write(void);
extern void test_cam_alloc(void);

extern void test_vec3_add(void);
extern void test_vec3_sub(void);
extern void test_vec3_mul(void);
extern void test_vec3_cross(void);
extern void test_vec3_length(void);
extern void test_vec3_dot(void);
extern void test_vec3_normalize(void);

extern void test_ray_center(void);
extern void test_ray_is_normalized(void);
extern void test_ray_directions_differ(void);

extern void test_scene_load_valid(void);
extern void test_scene_load_invalid_0(void);
extern void test_scene_load_invalid_1(void);
extern void test_scene_load_nothing(void);

extern void test_ray_sphere_intersection(void);
extern void test_ray_box_intersection(void);
extern void test_first_scene_collision_returns_closest_sphere(void);
extern void test_first_scene_collision_returns_box(void);

extern void test_config_load(void);

void setUp(void) {}
void tearDown(void) {}

int main(void) {
    UNITY_BEGIN();

    // IMAGES
    RUN_TEST(test_img_alloc);
    RUN_TEST(test_img_write);

    // SCENES
    RUN_TEST(test_scene_load_valid);
    RUN_TEST(test_scene_load_invalid_0);
    RUN_TEST(test_scene_load_invalid_1);
    RUN_TEST(test_scene_load_nothing);

    // CAMERA
    RUN_TEST(test_cam_alloc);

    // VEC3
    RUN_TEST(test_vec3_add);
    RUN_TEST(test_vec3_sub);
    RUN_TEST(test_vec3_dot);
    RUN_TEST(test_vec3_normalize);
    RUN_TEST(test_vec3_mul);
    RUN_TEST(test_vec3_cross);
    RUN_TEST(test_vec3_length);

    // RAY
    RUN_TEST(test_ray_center);
    RUN_TEST(test_ray_is_normalized);
    RUN_TEST(test_ray_directions_differ);

    // INTERSECTIONS
    RUN_TEST(test_ray_sphere_intersection);
    RUN_TEST(test_ray_box_intersection);
    RUN_TEST(test_first_scene_collision_returns_closest_sphere);
    RUN_TEST(test_first_scene_collision_returns_box);

    return UNITY_END();
}
