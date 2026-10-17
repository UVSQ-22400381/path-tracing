#include "unity.h"
#include <stdlib.h>
#include <stdio.h>
#include "renderer.h"

void test_img_alloc(void) {
    struct Image image = new_img(10, 5);
    TEST_ASSERT_NOT_NULL(image.pixels);
    TEST_ASSERT_EQUAL(image.width, 10);
    TEST_ASSERT_EQUAL(image.height,  5);
    free_image(&image);
}

void test_img_write(void) {
    struct Image image = new_img(10, 5);
    struct Pixel *pixs = image.pixels;
    for (size_t i = 0; i < image.width; i++) {
        pixs[image.width + i] = (struct Pixel){255, 0, 0};
    }

    const int code = save_img_ascii(&image, "./test_image.ppm");
    TEST_ASSERT_EQUAL(code, 0);
    free_image(&image);
}
