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

void setUp(void) {}
void tearDown(void) {}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_img_alloc);
    RUN_TEST(test_img_write);
    RUN_TEST(test_cam_alloc);
    RUN_TEST(test_vec3_add);
    RUN_TEST(test_vec3_sub);
    RUN_TEST(test_vec3_dot);
    RUN_TEST(test_vec3_normalize);
    RUN_TEST(test_vec3_mul);
    RUN_TEST(test_vec3_cross);
    RUN_TEST(test_vec3_length);
    RUN_TEST(test_ray_center);
    RUN_TEST(test_ray_is_normalized);
    RUN_TEST(test_ray_directions_differ);
    return UNITY_END();
}
