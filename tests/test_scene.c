#include "unity.h"
#include <stdlib.h>
#include <stdio.h>
#include "scene.h"

void test_scene_load(void) {
    int code = load_scene("./scene-0.txt");
    TEST_ASSERT_EQUAL(code, 0);
}
