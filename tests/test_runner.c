#include "unity.h"

extern void test_img_alloc(void);
extern void test_img_write(void);

extern void test_scene_load_valid(void);
extern void test_scene_load_invalid_0(void);
extern void test_scene_load_invalid_1(void);
extern void test_scene_load_nothing(void);

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
    return UNITY_END();
}
