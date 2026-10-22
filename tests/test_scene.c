#include "unity.h"
#include <stdlib.h>
#include <stdio.h>
#include "scene.h"

void test_scene_load(void) {
    struct Scene scene = load_scene_file("./scene-0.txt");
    TEST_ASSERT(scene.shapetypes != NULL);
    TEST_ASSERT(scene.shapes != NULL);
    TEST_ASSERT(scene.n > 0);
}
