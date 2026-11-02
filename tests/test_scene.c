#include "unity.h"
#include <stdlib.h>
#include <stdio.h>
#include "scene.h"

void test_scene_load_valid(void) {
    struct Scene scene = load_scene_file("./tests/test_scenes/scene_valid.txt");
    TEST_ASSERT(scene.shapetypes != NULL);
    TEST_ASSERT(scene.shapes != NULL);
    TEST_ASSERT(scene.n == 5);

    free_scene(&scene);
}

// NOTE:
// Need to find a way to test the invalid cases in one function
// while knowing which one fails/succeeds.

void test_scene_load_invalid_0(void) {
    struct Scene scene = load_scene_file("./tests/test_scenes/scene_invalid_0.txt");
    TEST_ASSERT(scene.shapetypes == NULL);
    TEST_ASSERT(scene.shapes == NULL);
    TEST_ASSERT(scene.n == 0);
}

void test_scene_load_invalid_1(void) {
    struct Scene scene = load_scene_file("./tests/test_scenes/scene_invalid_1.txt");
    TEST_ASSERT(scene.shapetypes == NULL);
    TEST_ASSERT(scene.shapes == NULL);
    TEST_ASSERT(scene.n == 0);
}

void test_scene_load_nothing(void) {
    struct Scene scene = load_scene_file("./tests/test_scenes/scene_comments.txt");
    TEST_ASSERT(scene.shapetypes != NULL);
    TEST_ASSERT(scene.shapes != NULL);
    TEST_ASSERT(scene.n == 0);

    free_scene(&scene);
}
