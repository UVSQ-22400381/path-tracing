#include "unity.h"

extern void test_img_alloc(void);
extern void test_img_write(void);

void setUp(void) {}
void tearDown(void) {}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_img_alloc);
    RUN_TEST(test_img_write);
    return UNITY_END();
}
