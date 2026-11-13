#include "unity.h"
#include <stdlib.h>
#include <stdio.h>
#include "scene.h"

void test_scene_load_valid(void) {
    struct Scene scene = load_scene_file("./tests/test_scenes/scene_valid.txt");

    // SHAPE TYPES
    TEST_ASSERT_NOT_NULL(scene.shapetypes);
    int types[5] = {0, 1, 0, 0, 1};
    TEST_ASSERT_EQUAL_INT_ARRAY(types, scene.shapetypes, 5);

    // COLORS
    TEST_ASSERT_NOT_NULL(scene.colors);

    TEST_ASSERT_EQUAL_CHAR(scene.colors[0].r, 0x11);
    TEST_ASSERT_EQUAL_CHAR(scene.colors[0].g, 0x11);
    TEST_ASSERT_EQUAL_CHAR(scene.colors[0].b, 0x11);

    TEST_ASSERT_EQUAL_CHAR(scene.colors[1].r, 0x22);
    TEST_ASSERT_EQUAL_CHAR(scene.colors[1].g, 0x22);
    TEST_ASSERT_EQUAL_CHAR(scene.colors[1].b, 0x22);

    TEST_ASSERT_EQUAL_CHAR(scene.colors[2].r, 0x33);
    TEST_ASSERT_EQUAL_CHAR(scene.colors[2].g, 0x33);
    TEST_ASSERT_EQUAL_CHAR(scene.colors[2].b, 0x33);

    TEST_ASSERT_NOT_NULL(scene.shapes);
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
