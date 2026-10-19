#include "unity.h"

extern void test_img_alloc(void);
extern void test_img_write(void);

extern void test_scene_load(void);

void setUp(void) {}
void tearDown(void) {}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_img_alloc);
    RUN_TEST(test_img_write);
    RUN_TEST(test_scene_load);
    return UNITY_END();
}
